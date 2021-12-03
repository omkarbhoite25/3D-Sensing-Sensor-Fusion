#include <opencv2/opencv.hpp>
#include <iostream>
#include <string> 
#include <fstream>
#include <sstream>
#include "main.h"
#include "time.h"


int main(int argc, char** argv) {

  ////////////////
  // Parameters //
  ////////////////

  // camera setup parameters
  double focal_length = 1247;
  double baseline = 213;

  // stereo estimation parameters
  int dmin = 67;
  int window_size = 3;
  double weight = 500;
  double scale = 3;

  ///////////////////////////
  // Commandline arguments //
  ///////////////////////////

  if (argc < 5) {
    std::cerr << "Usage: " << argv[0] << " IMAGE1 IMAGE2 OUTPUT_FILE" << std::endl;
    return 1;
  }

  cv::Mat image1 = cv::imread(argv[1], cv::IMREAD_GRAYSCALE);
  cv::Mat image2 = cv::imread(argv[2], cv::IMREAD_GRAYSCALE);
  const std::string output_file_naive = argv[3];
  const std::string output_file_dynamic_program = argv[4];

  if (!image1.data) {
    std::cerr << "No image1 data" << std::endl;
    return EXIT_FAILURE;
  }

  if (!image2.data) {
    std::cerr << "No image2 data" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout<<"window size : ";
	std::cin >> window_size;
	std::cout<<"weight : ";
	std::cin >> weight;
  std::cout<<"scale : ";
	std::cin >> scale;
	std::cout<<"dmin : ";
	std::cin >> dmin;
  std::cout<<"focal_length : ";
	std::cin >> focal_length;
	std::cout<<"baseline : ";
	std::cin >> baseline;


  std::cout << "------------------ Parameters -------------------" << std::endl;
  std::cout << "focal_length = " << focal_length << std::endl;
  std::cout << "baseline = " << baseline << std::endl;
  std::cout << "window_size = " << window_size << std::endl;
  std::cout << "occlusion weights = " << weight << std::endl;
  std::cout << "disparity added due to image cropping = " << dmin << std::endl;
  std::cout << "scaling of disparity images to show = " << scale << std::endl;
  std::cout << "output file path for naive program = " << argv[3] << std::endl;
  std::cout << "output file path for dynamic progran = " << argv[4] << std::endl;
  std::cout << "-------------------------------------------------" << std::endl;

  int height = image1.size().height;
  int width = image1.size().width;

  ////////////////////
  // Reconstruction //
  ////////////////////

  // Naive disparity image
  //cv::Mat naive_disparities = cv::Mat::zeros(height - window_size, width - window_size, CV_8UC1);
  cv::Mat naive_disparities = cv::Mat::zeros(height, width, CV_8UC1);

  StereoEstimation_Naive(
    window_size, dmin, height, width,
    image1, image2,
    naive_disparities, scale);

  ////////////
  // Output //
  ////////////

  // reconstruction
  Disparity2PointCloud(
    output_file_naive,
    height, width, naive_disparities,
    window_size, dmin, baseline, focal_length);

  // save / display images
  std::stringstream out1;
  out1 << output_file_naive << "stero_matching_naive.png";
  cv::imwrite(out1.str(), naive_disparities);
  cv::namedWindow("Naive", cv::WINDOW_AUTOSIZE);
  cv::imshow("Naive", naive_disparities);
  cv::waitKey(0);


  std::stringstream out2;
  cv::Mat t;
  t = DyanmicProgram_StereoMatching(image1,image2,window_size,weight);
  Disparity2PointCloud(
    output_file_dynamic_program,
    height, width, t,
    window_size, dmin, baseline, focal_length);
  out2 << output_file_dynamic_program << "stero_matching_dynamic_program.png";
  cv::imwrite(out2.str(), t);
  cv::namedWindow("t", cv::WINDOW_AUTOSIZE);
  cv::imshow("t", t);
  cv::waitKey(0);

  // Evaluation Metrics //
  double a = mean_sqared_error(image1,image2);
  std::cout << "Mean Squared Error " << a << std::endl;
  Structural_SImilarity_Measure(image1,image2,window_size);
  peak_signal_to_noise_ratio(image1,image2);
  return 0;
}

double Sumatrix_square_Differences(cv::Mat imgl, cv::Mat imgr, int h_size, int i, int j, int d,int ssd){
  for (int u = -h_size;u<=h_size;u++){
    for (int v = -h_size;v<=h_size;v++){
        int left_image_value = imgl.at < uchar > (i + u, j + v);	
        int right_image_value = imgr.at < uchar > (i + u, j + v + d);
        ssd += (left_image_value-right_image_value)*(left_image_value-right_image_value);
    }
  }
  return ssd;
}

double Sumatrix_square_Differences_normalized(cv::Mat imgl, cv::Mat imgr, int h_size, int i, int j, int d,int ssd, int nl,int nr, int window_size){
  for (int u = -h_size;u<=h_size;u++){
    for (int v = -h_size;v<=h_size;v++){
        int left_image_value = imgl.at < uchar > (i + u, j + v);	
        int right_image_value = imgr.at < uchar > (i + u, j + v + d);
        nl += left_image_value;
        nr += right_image_value;
    }
  }
  nl /= window_size*window_size;
  nr /= window_size*window_size;
  nl = std::max (1, nl);
  nr = std::max (1, nr);

  for (int u = -h_size;u<=h_size;u++){
    for (int v = -h_size;v<=h_size;v++){
        int left_image_value = imgl.at < uchar > (i + u, j + v);	
        int right_image_value = imgr.at < uchar > (i + u, j + v + d);
        ssd += (left_image_value/nl-right_image_value/nr)*(left_image_value/nl-right_image_value/nr);
    }
  }
  return ssd;
}


void StereoEstimation_Naive(
  const int& window_size,
  const int& dmin,
  int height,
  int width,
  cv::Mat& image1, cv::Mat& image2, cv::Mat& naive_disparities, const double& scale)
{
  clock_t tStart = clock();
  int half_window_size = window_size / 2;
  int p =0;
  #pragma omp parallel for 
  for (int i = half_window_size; i < height - half_window_size; ++i){

  #pragma omp critical
    {std::cout
      << "Calculating disparities for the naive approach... "
      << std::ceil(((p - half_window_size + 1) / static_cast<double>(height - window_size + 1)) * 100) << "%\r"
      << std::flush;
    }
    ++p;
    for (int j = half_window_size; j < width - half_window_size; ++j) {
      int min_ssd = INT_MAX;
      int disparity = 0;
      for (int d = -j + half_window_size; d < width - j - half_window_size; ++d) {
        int ssd = 0;
        int norm_left = 0;
        int norm_right = 0;
        ssd = Sumatrix_square_Differences(image1,image2,half_window_size,i,j,d,ssd);
        if (ssd < min_ssd) {
          min_ssd = ssd;
          disparity = d;
        }
      }
      naive_disparities.at<uchar>(i - half_window_size, j - half_window_size) = std::abs(disparity) * scale;
    }
  }
  std::cout << "Calculating disparities for the naive approach... Done.\r" << std::flush;
  std::cout << std::endl;
  printf("Time taken to complete naive approach: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
}


void Disparity2PointCloud(
  const std::string& output_file,
  int height, int width, cv::Mat& disparities,
  const int& window_size,
  const int& dmin, const double& baseline, const double& focal_length)
{
  clock_t tStart = clock();
  std::stringstream out3d;
  out3d << output_file << "3d.xyz";
  std::ofstream outfile(out3d.str());
  cv::Mat X = cv::Mat::zeros(disparities.size(), CV_32FC1);
	cv::Mat Y = cv::Mat::zeros(disparities.size(), CV_32FC1);
	cv::Mat Z = cv::Mat::zeros(disparities.size(), CV_32FC1);
  // #pragma omp parallel for
  for (int i = 0; i < height - window_size; ++i) {
    // #pragma omp critical
    {
      std::cout << "Reconstructing 3D point cloud from disparities... " << std::ceil(((i) / static_cast<double>(height - window_size + 1)) * 100) << "%\r" << std::flush;
    }    
    for (int j = 0; j < width - window_size; ++j) {
      if (disparities.at<uchar>(i, j) == 0) continue;
      const double Z = (focal_length*baseline)/(disparities.at<uchar>(i,j) + dmin);
      const double X = (-baseline*(i-(disparities.rows/2)+disparities.at<uchar>(i,j) + dmin))/(2*(disparities.at<uchar>(i,j) + dmin));
      const double Y = (baseline*(j-disparities.cols/2))/(disparities.at<uchar>(i,j) + dmin);
      outfile <<X << " " << Y << " " << Z << " " << std::endl;
    }
  }
// #pragma omp critical
  {
    std::cout << "Reconstructing 3D point cloud from disparities... Done.\r" << std::flush;
    std::cout << std::endl;
    printf("Time taken to complete 3D point cloud: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
  }
}


cv::Mat DyanmicProgram_StereoMatching(cv::Mat imgL, cv::Mat imgR, int Window_Size, int weight) {
  clock_t tStart = clock();
	cv::Size imageSize = imgL.size();
	cv::Mat disparities = cv::Mat::zeros(imageSize, CV_16UC1);
  int count = 0;
  #pragma omp parallel for
	for (int s = Window_Size; s < imageSize.height - Window_Size; ++s) {
		cv::Mat C = cv::Mat::zeros(cv::Size(imageSize.width - 2 * Window_Size, imageSize.width - 2 * Window_Size), CV_16UC1);
		cv::Mat M = cv::Mat::zeros(cv::Size(imageSize.width - 2 * Window_Size, imageSize.width - 2 * Window_Size), CV_8UC1);
		C.at<unsigned short>(0, 0) = 0;
		M.at<unsigned char>(0, 0) = 0;
		for (int i = 1; i < C.size().height; ++i) {
			C.at<unsigned short>(i, 0) = i * weight;
			M.at<unsigned char>(i, 0) = 1;
		}
		for (int j = 1; j < C.size().width; ++j) {
			C.at<unsigned short>(0, j) = j * weight;
			M.at<unsigned char>(0, j) = 2;
		}

		for (int r = 1; r < C.size().height; ++r) {
			for (int l = 1; l < C.size().width; ++l) {
				cv::Rect L_ROI = cv::Rect(l, s - Window_Size, 2 * Window_Size + 1, 2 * Window_Size + 1);
				cv::Rect R_ROI = cv::Rect(r, s - Window_Size, 2 * Window_Size + 1, 2 * Window_Size + 1);
				cv::Mat L_window = imgL(L_ROI);
				cv::Mat R_window = imgR(R_ROI);
				cv::Mat diff;
				absdiff(L_window, R_window, diff);
				int SAD = sum(diff)[0];
				int C_Match = C.at<unsigned short>(r - 1, l - 1) + SAD;
				int C_Left_Occlusion = C.at<unsigned short>(r - 1, l) + weight;
				int C_Right_Occlusion = C.at<unsigned short>(r, l - 1) + weight;
				int c = C_Match;
				int m = 0;
				if (C_Left_Occlusion < c) {
					c = C_Left_Occlusion;
					m = 1;
					if (C_Right_Occlusion < c) {
						c = C_Right_Occlusion;
						m = 2;
					}
				}

				C.at<unsigned short>(r, l) = c;
				M.at<unsigned char>(r, l) = m;
			}
		}

		int i = M.size().height - 1;
		int j = M.size().width - 1;
		while (j > 0) {
			switch (M.at<unsigned char>(i, j)) {
			case 0:
        if ((i-j)<0){
				  disparities.at<unsigned short>(s, j) = abs(i-j);
        }
        else{
          disparities.at<unsigned short>(s, j) = 0 ;
        }
				i--;
				j--;
				break;
			case 1:
        // disparities.at<unsigned short>(s, j) = 0;
				i--;
				break;
			case 2:
				// disparities.at<unsigned short>(s, j) = 0;
				j--;
				break;
			}
		}
    count += 1;
		#pragma omp critical
    {
      std::cout
      << "Calculating disparities for the dynamic program approach... "
      << std::ceil(((count - Window_Size + 1) / static_cast<double>(imageSize.height - 2*Window_Size)) * 100) << "%\r"
      << std::flush;
    }
	}

	cv::Mat a;
	disparities.convertTo(a, CV_8UC1);
  printf("Time taken to complete dynamic program approach: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
	return a;
};


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


