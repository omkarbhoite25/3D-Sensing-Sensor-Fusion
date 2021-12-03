#pragma once

void StereoEstimation_Naive(
  const int& window_size,
  const int& dmin,
  int height,
  int width,
  cv::Mat& image1, cv::Mat& image2, cv::Mat& naive_disparities, const double& scale);

void Disparity2PointCloud(
  const std::string& output_file,
  int height, int width, cv::Mat& disparities,
  const int& window_size,
  const int& dmin, const double& baseline, const double& focal_length);

cv::Mat DyanmicProgram_StereoMatching(cv::Mat imgL, cv::Mat imgR, int Window_Size, int weight);
double mean_sqared_error(cv::Mat input_image1,cv::Mat input_image2);
double peak_signal_to_noise_ratio(cv::Mat input_image1,cv::Mat input_image2);
double var(cv::Mat & matrix, int i, int j, int window_size);
double Covariance(cv::Mat & input_image1, cv::Mat & input_image2, int i, int j, int block_size);
double Structural_SImilarity_Measure(cv::Mat input_image1,cv::Mat input_image2, int window_size);
