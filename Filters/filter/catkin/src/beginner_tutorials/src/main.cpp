#define _USE_MATH_DEFINES
#include <iostream>
#include <opencv2/opencv.hpp>

cv::Mat Gaussian_Kernel(int window_size, float sigma) {
    
  cv::Mat kernel(cv::Size(window_size, window_size), CV_32FC1);

  int half_window_size = window_size / 2;
  if (sigma == 0){
        const double k = 2.5;
        const double r_max = std::sqrt(2.0 * half_window_size * half_window_size);
        const double sigma = r_max / k;

        // sum is for normalization 
        float sum = 0.0;

        for (int x = -window_size / 2; x <= window_size / 2; x++) {
            for (int y = -window_size / 2; y <= window_size / 2; y++) {
                float val = exp(-(x * x + y * y) / (2 * sigma * sigma));
                kernel.at<float>(x + window_size / 2, y + window_size / 2) = val;
                sum += val;
            }
        }

        for (int i = 0; i < 5; ++i)
        for (int j = 0; j < 5; ++j)
        kernel.at<float>(i, j) /= sum;
        
    }

    else{
        std::cout<<"Hi"<<std::endl;
        double sum = 0.0;
        double i, j;
        for (i = 0; i < window_size; i++) {
            for (j = 0; j < window_size; j++) {
                kernel.at<float>(i, j) = exp(-(i * i + j * j) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
                sum += kernel.at<float>(i, j);
            }
        }
        for (i = 0; i < window_size; i++) {
            for (j = 0; j < window_size; j++) {
                kernel.at<float>(i, j) /= sum;
            }
        }
    }

  return kernel;
}

cv::Mat Box_Filter(const cv::Mat& input, const int window_size = 5) {

  const auto width = input.cols;
  const auto height = input.rows;
  cv::Mat output = cv::Mat::zeros(height,width,CV_32FC1);
  for (int r = window_size / 2; r < height - window_size / 2; ++r) {
    for (int c = window_size / 2; c < width - window_size / 2; ++c) {

      // box filter
      int sum = 0;
      for (int i = -window_size / 2; i <= window_size / 2; ++i) {
        for (int j = -window_size / 2; j <= window_size / 2; ++j) {
          sum += input.at<uchar>(r + i, c + j);
        }
      }
      output.at<uchar>(r, c) = sum / (window_size * window_size);
    }
  }
  return output;
}

cv::Mat Gaussian_Filter(const cv::Mat& input, const int window_size = 5) {

  const auto width = input.cols;
  const auto height = input.rows;
  int hsize = window_size/2;
  cv::Mat output = cv::Mat::zeros(height,width,input.type());
  cv::Mat gaussianKernel = Gaussian_Kernel(window_size,0);

  for (int r = window_size / 2; r < height - window_size / 2; ++r) {
    for (int c = window_size / 2; c < width - window_size / 2; ++c) {

      int sum = 0;
      for (int i = -window_size / 2; i <= window_size / 2; ++i) {
        for (int j = -window_size / 2; j <= window_size / 2; ++j) {
          sum
            += input.at<uchar>(r + i, c + j)
            * gaussianKernel.at<float>(i + window_size / 2, j + window_size / 2);
        }
      }
      output.at<uchar>(r, c) = sum;

    }
  }
  std::cout << "Gaussian Filter" << std::endl;
  return output;
}

cv::Mat Bilateral_Filter(const cv::Mat& input, const int window_size = 5,float SpectralSigma = 5,float SpatialSigma = 0.5) {
  clock_t tStart = clock();
  const auto width = input.cols;
  const auto height = input.rows;

  cv::Mat gaussianKernel = Gaussian_Kernel(window_size,SpatialSigma);
  cv::Mat output = cv::Mat::zeros(height,width,input.type());

  auto d = [](float a, float b) {
    return std::abs(a - b);
  };

  auto p = [](float val,float SpectralSigma ) {
    const float sigma = SpectralSigma;
    const float sigmaSq = SpectralSigma * SpectralSigma;
    const float normalization = std::sqrt(2*M_PI) * sigma;
    return (1 / normalization) * std::exp(-val / (2 * sigmaSq));
  };

  for (int r = window_size / 2; r < height - window_size / 2; ++r) {
    for (int c = window_size / 2; c < width - window_size / 2; ++c) {

      float sum_w = 0;
      float sum = 0;

      for (int i = -window_size / 2; i <= window_size / 2; ++i) {
        for (int j = -window_size / 2; j <= window_size / 2; ++j) {

          float range_difference
            = d(input.at<uchar>(r, c), input.at<uchar>(r + i, c + j));

          float w 
            = p(range_difference,SpectralSigma)
            * gaussianKernel.at<float>(i + window_size / 2, j + window_size / 2);

          sum
            += input.at<uchar>(r + i, c + j) * w;
          sum_w
            += w;
        }
      }

      output.at<uchar>(r, c) = sum / sum_w;

    }
  }
  printf("Time taken to complete bilateral filter operation is : %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  return output;
}


cv::Mat Joint_Bilateral(const cv::Mat& input_rgb, const cv::Mat& input_depth, cv::Mat& output, const int window_size = 5, float SpectralSigma = 5,float SpatialSigma = 0.5) {
    clock_t tStart = clock();
    const auto width = input_rgb.cols;
    const auto height = input_rgb.rows;

    cv::Mat gaussianKernel = Gaussian_Kernel(window_size, SpatialSigma); 
    auto d = [](float a, float b) {
        return std::abs(a - b);
    };

    auto p = [](float val, float SpectralSigma) {	
        const float sigmaSq = SpectralSigma * SpectralSigma;
        const float normalization = std::sqrt(2 * M_PI) * SpectralSigma;
        return (1 / normalization) * std::exp(-val / (2 * sigmaSq));
    };

    for (int r = window_size / 2; r < height - window_size / 2; ++r) {
        for (int c = window_size / 2; c < width - window_size / 2; ++c) {

            float sum_w = 0;
            float sum = 0;

            for (int i = -window_size / 2; i <= window_size / 2; ++i) {
                for (int j = -window_size / 2; j <= window_size / 2; ++j) {

                    float range_difference = d(input_rgb.at<uchar>(r, c), input_rgb.at<uchar>(r + i, c + j)); 
                    float w = p(range_difference, SpectralSigma) * gaussianKernel.at<float>(i + window_size / 2, j + window_size / 2); 
                    sum += input_depth.at<uchar>(r + i, c + j) * w; 
                    sum_w += w;
                }
            }
            output.at<uchar>(r, c) = sum / sum_w;
        }
    }
    printf("Time taken to complete joint bilateral filter operation is : %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return output;
}

cv::Mat Upsampling(const cv::Mat& input_rgb, const cv::Mat& input_depth,const int window_size = 5, float SpectralSigma = 0.1,float SpatialSigma = 0.5) {
  clock_t tStart = clock();
  int uf = log2(input_rgb.rows / input_depth.rows); // upsample factor
  cv::Mat D = input_depth.clone(); // lower depth image
  cv::Mat I = input_rgb.clone(); // rgb image
  for (int i = 0; i < uf; ++i)
  {
    cv::resize(D,D,D.size(), 0.5, 0.5, CV_INTER_CUBIC);
    // cv::resize(D, D, D.size() * 2); // doubling the size of the depth image
    cv::resize(I, I, D.size());		// resizing the rgb image to depth image size
    Joint_Bilateral(I, D, D, window_size, SpectralSigma,SpatialSigma); // applying the joint bilateral filter with changed size depth and rbg images
  }
  cv::resize(D, D, input_rgb.size()); // in the end resizing the depth image to rgb image size
  Joint_Bilateral(input_rgb, D, D, window_size, SpectralSigma,SpectralSigma); // applying the joint bilateral filter with full res. size images
  printf("Time taken to complete upsampling guided joint bilateral filter operation is : %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  return D;
}

cv::Mat synthetic_depth_generation(cv::Mat input_image){
  // const auto width = input_image.cols;
  // const auto height = input_image.rows;
  // cv::Mat output = cv::Mat::zeros(height,width,input_image.type());
  // cv::Mat I = input_image.clone();
  // cv::resize(input_image,output,CV_INTER_LINEAR);
  cv::resize(input_image, input_image, input_image.size()/3,8,8,CV_INTER_AREA);
  // cv::resize(input_image, input_image, I.size());
  // cv::Mat near_img,bilinear_img,bicubic_img;
  // cv::pyrDown(input_image,input_image);
  // cv::resize(input_image,near_img,input_image.size(), 10, 10, CV_INTER_NN);
  // cv::resize(input_image,bilinear_img,input_image.size(), 10, 10, CV_INTER_LINEAR);
  // cv::resize(input_image,bicubic_img,input_image.size(), 10, 10, CV_INTER_CUBIC);
  cv::Mat noise(input_image.size(), input_image.type());
  float mean = 5; // default
  float stddev = 15; // default
  cv::randn(noise, mean, stddev);
  input_image += noise;
  // return input_image,near_img,bilinear_img,bicubic_img;
  return input_image;
}






double mean_sqared_error(cv::Mat input_image1,cv::Mat input_image2){
  int i , j;
  double mse = 0;
  int height = input_image1.rows;
  int width = input_image1.cols;
  for (i = 0; i< height;i++){
    for (j = 0; j< width;j++){
      mse += pow((input_image1.at<uchar>(i,j) - input_image2.at<uchar>(i,j)),2);
    }
  }
  mse /=height*width;
  mse /= 100;
  return mse;
}


double peak_signal_to_noise_ratio(cv::Mat input_image1,cv::Mat input_image2){
  int a = 255;
  double b = (10* log10((a*a)/mean_sqared_error(input_image1,input_image2)));
  std::cout << "Peak Signal to Noise Ratio : " << b << std::endl;
}

double var(cv::Mat & matrix, int i, int j, int window_size){
  double sd = 0;
  cv::Mat matrix_tmp = matrix(cv::Range(i, i + window_size), cv::Range(j, j + window_size));
  cv::Mat matrix_square(window_size, window_size, CV_64FC1);
  multiply(matrix_tmp, matrix_tmp, matrix_square);
  double avg = mean(matrix_tmp)[0];
  double avg_2 = mean(matrix_square)[0];
  sd = sqrt(avg_2 - avg * avg);
  if (isnan(sd) == 1){
    sd = avg;
  }
  // std::cout <<  "sd" << sd << std::endl;
  return sd;
}

double Covariance(cv::Mat & input_image1, cv::Mat & input_image2, int i, int j, int block_size){
  cv::Mat m3 = cv::Mat::zeros(block_size, block_size, input_image1.depth());
  cv::Mat input_image1_tmp = input_image1(cv::Range(i, i + block_size), cv::Range(j, j + block_size));
  cv::Mat input_image2_tmp = input_image2(cv::Range(i, i + block_size), cv::Range(j, j + block_size));
  multiply(input_image1_tmp, input_image2_tmp, m3);
  double avg_ro 	= mean(m3)[0];
  double avg_r 	= mean(input_image1_tmp)[0];
  double avg_o 	= mean(input_image2_tmp)[0]; 
  double sd_ro = avg_ro - avg_o * avg_r; 
  return sd_ro;
}


double Structural_SImilarity_Measure(cv::Mat input_image1,cv::Mat input_image2, int window_size){
  double ssim = 0;
  std::array<double,0> f;
  int i,j;
  int a = input_image1.rows/window_size;
  int b = input_image2.cols/window_size;
  double C1 = pow(0.01 * 255,2);
  double C2 = pow(0.03 * 255,2);
  for (i = 0; i< a;i++){
    for (j = 0; j< b;j++){
      int m = i*window_size;
      int n = j*window_size;
      double avg_1 = mean(input_image1(cv::Range(i,i+window_size),cv::Range(j,j+window_size)))[0];
      double avg_2 = mean(input_image2(cv::Range(i,i+window_size),cv::Range(j,j+window_size)))[0];
      double var_1 = var(input_image1,m,n,window_size);
      double var_2 = var(input_image2,m,n,window_size);
      double covariance = Covariance(input_image1,input_image2,m,n,window_size);
      ssim += ((2*avg_1*avg_2+C1)*(2*covariance+C2))/((pow(avg_1,2)+pow(avg_2,2)+C1)*(pow(var_1,2)+pow(var_2,2)+C2)); 
      // std::cout<<"avg_1"<<avg_1<<std::endl;
      // std::cout<<"avg_2"<<avg_2<<std::endl;
      // std::cout<<"var_1"<<var_1<<std::endl;
      // std::cout<<"var_2"<<var_2<<std::endl;
      // std::cout<<"covariance"<<covariance<<std::endl;
    }
    // std::cout<<ssim<<std::endl;
  }
  ssim /= a*b;
  std::cout << "Structural SImilarity Measure : " << ssim << std::endl;
  return ssim;
}





int main(int argc, char** argv){
    if (argc < 3) {
        std::cerr << " IMAGE1 OUTPUT_FILE" << std::endl;
        return 1;
    }
    cv::Mat image = cv::imread(argv[1],0);
    cv::Mat color = cv::imread(argv[1]);
    const std::string output_file = argv[2];
    std::stringstream out0,out3,out1,out2;
    // std::cerr << image.type() << std::endl;
    if (image.data == nullptr) {
    std::cerr << "Failed to load image" << std::endl;
    }
    /////////////////////////////////////////////////////////////////////
    // cv::imshow("Original Image", image);
    out0 << output_file << "Original_Image.png";
    cv::imwrite(out0.str(),image);
    // cv::waitKey(0);
    ///////////////////////////////////////////////////////////////////////
    cv::Mat noise(image.size(), image.type());
    float mean = 5; // default
    float stddev = 25; // default
    // std::cout<<"Mean : ";
    // std::cin >> mean;
    // std::cout<<"Standard Deviation : ";
    // std::cin >> stddev;
    cv::randn(noise, mean, stddev);
    image += noise;
    // // color += noise;
    // out3 << output_file << "Noise_added_to_original_image.png";
    // cv::imwrite(out3.str(),image);
    // cv::imshow("Noise added to original image", image);
    // // cv::waitKey(0);
    // //////////////////////////////////////////////////////////////////////
    // cv::Mat GaussianOutput = Gaussian_Filter(image);
    // out1 << output_file << "Gaussian_Filter.png";
    // cv::imwrite(out1.str(),GaussianOutput);
    // // cv::imshow("Gaussian_Filter", GaussianOutput);
    // // cv::waitKey(0);
    // // ///////////////////////////////////////////////////////////////////////
    // float Spectral_Sigma = 0;
    // float Spatial_Sigma = 0;
    // // std::cout<<"Window Size : ";
    // // std::cin >> window_size;
    // std::cout<<"Spectral Sigma : ";
    // std::cin >> Spectral_Sigma;
    // std::cout<<"Spatial Sigma : ";
    // std::cin >> Spatial_Sigma;
    // cv::Mat BilateralOutput = Bilateral_Filter(image,5,Spectral_Sigma,Spatial_Sigma);
    // out2 << output_file << "Bilateral_Filter.png";
    // cv::imwrite(out2.str(),BilateralOutput);
    // cv::imshow("Bilateral_Filter", BilateralOutput);
    ////////////////////////////////////////////////////////////////////////
    int window_size = 3;
    float Spectral_Sigma = 0;
    float Spatial_Sigma = 0;
    std::cout<<"Window Size : ";
    std::cin >> window_size;
    std::cout<<"Spectral Sigma : ";
    std::cin >> Spectral_Sigma;
    std::cout<<"Spatial Sigma : ";
    std::cin >> Spatial_Sigma;
    // cv::imshow("Original Color Image", color);
    cv::Mat a = cv::imread("/home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/Input_Images/Art/Art/view1.png",0);
    // cv::Mat a_bl = cv::imread("/home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output gifts/Joint_Bilateral_Filter_bl_5_5.png",0);
    // cv::Mat a_cu = cv::imread("/home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output gifts/Joint_Bilateral_Filter_cu_5_5.png",0);
    cv::Mat b = cv::imread("/home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/Stereo_Matching/Output_Images/Art/Naive/stero_matching_naive.png",0);
    cv::Mat d = synthetic_depth_generation(b);
    out2 << output_file << "Down_Sampled_With_Noise.png";
    cv::imwrite(out2.str(),d);
    // cv::PSNR()
    // cv::Mat a = cv::imread(argv[1],0);
    // cv::Mat b = image;
    // cv::imshow("a", a);
    // cv::imshow("b", d);
    cv::Mat JointBilateralOutput = Upsampling(a,d,window_size,Spectral_Sigma,Spatial_Sigma);
    out3 << output_file << "Joint_Bilateral_Filter.png";
    cv::imwrite(out3.str(),JointBilateralOutput);
    std::cout << window_size<<" "<<Spectral_Sigma<<" "<<Spatial_Sigma<<std::endl;
    cv::imshow("Joint_Bilateral_Filter", JointBilateralOutput);
    // cv::waitKey(0);
    ///////////////////////////////////////////////////////////////////////
    // gaussian
    // cv::GaussianBlur(im, output, cv::Size(5, 5), 0, 0);
    // cv::imshow("gaussian", output);
    //cv::waitKey();
    // median
    // cv::medianBlur(im, output, 3);
    // cv::imshow("median", output);
    //cv::waitKey();
    // std::cout << "PSNR" <<cv::PSNR(a,b) << std::endl;
    // double m = Structural_SImilarity_Measure(a,b,5);

    // std::cout << "PSNR" <<cv::PSNR(a_bl,b) << std::endl;
    // double n = Structural_SImilarity_Measure(a_bl,b,5);


    // std::cout << "PSNR" <<cv::PSNR(a_cu,b) << std::endl;
    // double q = Structural_SImilarity_Measure(a_cu,b,5);
    // // bilateral
    // double window_size = 11;
    // cv::bilateralFilter(im, output, window_size, 2 * window_size, window_size / 2);
    // cv::imshow("bilateral", output);

    // output = Box_Filter(im);
    // cv::imshow("Box_Filter", output);

    // cv::Mat d = synthetic_depth_generation(a);
    // cv::imshow("Synthetic Depth Generation", d);
    // cv::imshow("Joint_Bilateral_Filter", JointBilateralOutput);
    
    cv::waitKey();
    return 0;
}


























