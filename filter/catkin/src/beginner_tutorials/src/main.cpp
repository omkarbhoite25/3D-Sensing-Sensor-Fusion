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

cv::Mat Bilateral_Filter(const cv::Mat& input, const int window_size = 5) {
  const auto width = input.cols;
  const auto height = input.rows;

  cv::Mat gaussianKernel = Gaussian_Kernel(window_size,0);
  cv::Mat output = cv::Mat::zeros(height,width,input.type());

  auto d = [](float a, float b) {
    return std::abs(a - b);
  };

  auto p = [](float val) {
    const float sigma = 5;
    const float sigmaSq = sigma * sigma;
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
            = p(range_difference)
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
  return output;
}


cv::Mat Joint_Bilateral(const cv::Mat& input_rgb, const cv::Mat& input_depth, cv::Mat& output, const int window_size = 5, float SpectralSigma = 5,float SpatialSigma = 0.5) {
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
    return output;
}

cv::Mat Upsampling(const cv::Mat& input_rgb, const cv::Mat& input_depth,const int window_size = 5, float SpectralSigma = 0.1,float SpatialSigma = 0.5) {
  int uf = log2(input_rgb.rows / input_depth.rows); // upsample factor
  cv::Mat D = input_depth.clone(); // lowres depth image
  cv::Mat I = input_rgb.clone(); // highres rgb image
  for (int i = 0; i < uf; ++i)
  {
    cv::resize(D, D, D.size() * 2); // doubling the size of the depth image
    cv::resize(I, I, D.size());		// resizing the rgb image to depth image size
    Joint_Bilateral(I, D, D, window_size, SpectralSigma,SpatialSigma); // applying the joint bilateral filter with changed size depth and rbg images
  }
  cv::resize(D, D, input_rgb.size()); // in the end resizing the depth image to rgb image size
  Joint_Bilateral(input_rgb, D, D, window_size, SpectralSigma,SpectralSigma); // applying the joint bilateral filter with full res. size images
  return D;
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
    std::cerr << image.type() << std::endl;
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
    float mean = 0; // default
    float stddev = 1; // default
    std::cout<<"Mean : ";
    std::cin >> mean;
    std::cout<<"Standard Deviation : ";
    std::cin >> stddev;
    cv::randn(noise, mean, stddev);
    image += noise;
    // color += noise;
    out3 << output_file << "Noise_added_to_original_image.png";
    cv::imwrite(out3.str(),image);
    // cv::imshow("Noise added to original image", image);
    // cv::waitKey(0);
    //////////////////////////////////////////////////////////////////////
    cv::Mat GaussianOutput = Gaussian_Filter(image);
    out1 << output_file << "Gaussian_Filter.png";
    cv::imwrite(out1.str(),GaussianOutput);
    // cv::imshow("Gaussian_Filter", GaussianOutput);
    // cv::waitKey(0);
    ///////////////////////////////////////////////////////////////////////
    cv::Mat BilateralOutput = Bilateral_Filter(image);
    out2 << output_file << "Bilateral_Filter.png";
    cv::imwrite(out2.str(),BilateralOutput);
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
    cv::Mat a = cv::imread("/home/omkar/ELTE/ELTE/3DSSF/02_opencv_filters/catkin/src/beginner_tutorials/include/cones-ppm-9/cones/im2.ppm",0);
    cv::Mat b = cv::imread("/home/omkar/ELTE/ELTE/3DSSF/02_opencv_filters/catkin/src/beginner_tutorials/include/cones-ppm-9/cones/disp.pgm",0);
    cv::imshow("a", a);
    cv::imshow("b", b);
    cv::Mat JointBilateralOutput = Upsampling(a,b,window_size,Spectral_Sigma,Spatial_Sigma);
    // out2 << output_file << "Joint_Bilateral_Filter.png";
    // cv::imwrite(out2.str(),JointBilateralOutput);
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

    // bilateral
    // double window_size = 11;
    // cv::bilateralFilter(im, output, window_size, 2 * window_size, window_size / 2);
    // cv::imshow("bilateral", output);

    // output = Box_Filter(im);
    // cv::imshow("Box_Filter", output);

    
    
    


    // HW (1 point for each metric, max 5 points):
    // - compare your images
    //		- SSD
    //		- RMSE (Root Mean Squared Error)
    //		- PSNR ..
    //	  - ....
    cv::waitKey(0);
    return 0;
}































// // #include <iostream>
// // #include <opencv2/opencv.hpp>
// // #include <string> 
// // #include <fstream>
// // #include <sstream>
// // #include <time.h>
// // #include <chrono>
// // using namespace std;

// // typedef vector<double> Array;
// // typedef vector<Array> Matrix;
// // typedef vector<Matrix> Image;

// // Matrix gaussianFilter(int h, int w, double sd){
// // 	Matrix kernel(h, Array(w));
// // 	std::cout << "Inital Kernel matrix"  <<std::endl;
// // 	double sum=0.0;
// // 	for (int i =  0; i < h ; ++i) {
// // 		for (int j =  0; j <w; ++j){
// // 			kernel[i][j] = (exp(-((i*i+j*j) / (2*sd*sd)))) / ( 2*M_PI * sd*sd);
// // 			sum += kernel[i][j];

// // 		}
// // 	}
// // 	for (int i = 0; i < h; ++i){
// // 		for (int j = 0; j < w; ++j){
// // 			kernel[i][j] /= sum;
// // 		cout << kernel[i][j];
// // 		}
// // 	}
// // 	return kernel;
// // }


// // void customFilter(const cv::Mat& input, cv::Mat& output){
// // 	const auto width = input.cols;
// // 	const auto height = input.rows;
// // 	const int window_size = 7;
// // 	// TEMPORARY CODE
// // 	for (int r = 0; r < height; ++r) {
// // 		for (int c = 0; c < width; ++c) {
// // 			output.at<uchar>(r, c) = 0;
// // 		}
// // 	}
// // 	Matrix kernel(window_size, Array(window_size));
// // 	// std::cout << kernel;
// // 	for (int r = window_size / 2; r < height - window_size / 2; ++r) {
// // 		for (int c = window_size / 2; c < width - window_size / 2; ++c){
// // 			// kernel.at<uchar> (r,c) += input.at<uchar>(r,c) * a;
// // 			double sum = 0.0;
// // 			double sd = 5.0;
// // 			for (int i = 0; i <window_size; ++i) {
// // 				for (int j = 0; j < window_size ; ++j) {
// // 					kernel[i][j] = (exp(-((i*i+j*j) / (2*sd*sd)))) / ( 2*M_PI * sd*sd);
// // 					sum += kernel[i][j];
// // 				}
// // 			}
// // 			// cout << sum ;
// // 			for (int i = 0; i < window_size ; ++i){
// // 				for (int j = 0; j < window_size ; ++j){
// // 					kernel[i][j] /= sum;
// // 				// cout << kernel[i][j];
// // 				// cout<< "/n" <<j;
// // 				}
// // 			}
// // 			// cout << "size "<<kernel[0][0];
// // 			for (int i = 0; i <window_size ; ++i) {
// // 				for (int j = 0; j <window_size ; ++j) {
// // 					output.at<uchar>(r+i, c+j) += input.at<uchar>(r+i,c+j)*kernel[i][j];
// // 				}
// // 			}
// // 		}
// // 	}
// // }




// // int main(int argc, char** argv) {
// // 	if (argc < 1) {
// // 		std::cerr << " IMAGE1 " << std::endl;
// // 		return 1;
// //   	}
// // 	cv::Mat im = cv::imread(argv[1],cv::IMREAD_COLOR);

// // 	if (im.data == nullptr) {
// // 		std::cerr << "Failed to load image" << std::endl;
// // 	}

// // 	cv::imshow("im", im);
// // 	cv::waitKey(0);

// // 	cv::Mat noise(im.size(), im.type());
// // 	uchar mean = 0;
// // 	uchar stddev = 25;
// // 	cv::randn(noise, mean, stddev);


// // 	im += noise;

// // 	cv::imshow("im", im);
// // 	//cv::waitKey();

// // 	// gaussian
// // 	cv::Mat output;
// // 	cv::GaussianBlur(im, output, cv::Size(7, 7), 0, 0);
// // 	cv::imshow("gaussian", output);
// // 	//cv::waitKey();

// // 	// median
// // 	cv::medianBlur(im, output, 3);
// // 	cv::imshow("median", output);
// // 	//cv::waitKey();

// // 	// bilateral
// // 	double window_size = 11;
// // 	cv::bilateralFilter(im, output, window_size, 2 * window_size, window_size / 2);
// // 	cv::imshow("bilateral", output);

// // 	customFilter(im, output);
// // 	cv::imshow("OurFiler", output);

// // 	cv::waitKey();

// // 	// HW (1 point for each metric, max 5 points):
// // 	// - compare your images
// // 	//		- SSD
// // 	//		- RMSE (Root Mean Squared Error)
// // 	//		- PSNR ..
// // 	//	  - ....

// // 	return 0;
// // }