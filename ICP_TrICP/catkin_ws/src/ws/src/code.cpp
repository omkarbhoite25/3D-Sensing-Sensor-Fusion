#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include "ros/ros.h"
#include "math.h"
#include </home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/ICP_TrICP/catkin_ws/src/ws/src/nanoflann.hpp>
#include <eigen3/Eigen/Dense>
#include <chrono> 
#include <random>
#include <fstream>
using namespace std;
using namespace cv;
using namespace nanoflann;
using namespace std::chrono;


int K = 5;
int MAX_ITERATIONS = 200;
int NUM_OF_TR_POINTS = 1000;
int AddNoiseToPointCloud = 0;

string OUTPUT_FILE = "/home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/ICP_TrICP/catkin_ws/src/ws/include/output.xyz";
string OUTPUT_FILE_FUSE = "/home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/ICP_TrICP/catkin_ws/src/ws/include/fuse.xyz";
const double ERROR_DROP_THRESH = 0.0001; //iterative_closest_point
const double iterative_closest_point_ERROR_LOW_THRESH = 0.01; //iterative_closest_point
const double DIST_DROP_THRESH = 150.0; //Tr-iterative_closest_point
const double ERROR_LOW_THRESH = 0.05; //Tr-iterative_closest_point

double previousError = 0;

void searchNN(const Eigen::MatrixXf & cloud1,const Eigen::MatrixXf & cloud2, const size_t k,Eigen::MatrixXi &indices,Eigen::MatrixXf &dists, const bool return_dist_squared);
int PointCloudProcessing(string file_path, vector<Point3d >& out_points);
void sort_matr(const Eigen::MatrixXf &m,Eigen::MatrixXf &out, Eigen::MatrixXi &indexes, int to_save);
int tr_iterative_closest_point(const Eigen::MatrixXf &src,const Eigen::MatrixXf &dst,Eigen::MatrixXf &srcTransformation, const int max_itreations,const double error_low_thresh,  const double dist_drop_thresh,const int Npo);
int iterative_closest_point(const Eigen::MatrixXf &src,const Eigen::MatrixXf &dst,Eigen::MatrixXf &srcTransformation,const int max_itreations,const double error_drop_thresh);
int EigenJacboiSVD(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B,Eigen::Matrix3d &R,Eigen::Vector3d &t );
Eigen::MatrixXf fuse(const Eigen::MatrixXf &cloud1,const Eigen::MatrixXf &cloud2);



int main(int argc, char ** argv){
  int K = 5;
  int MAX_ITERATIONS = 200;
  int NUM_OF_TR_POINTS = 1000;
  int AddNoiseToPointCloud = 0;
  int CHOOSE = 0;

  cout<<"Choose 1 for ICP or 2 for Tr-ICP: ";
  cin>>CHOOSE;
  cout<<"Number of neighbours to be used: ";
  cin>>K;
  cout << "Number of iteration: ";
  cin >> MAX_ITERATIONS;
  cout <<"Add nosie to the point cloud, if yes then write 1; else the point cloud will be processed as normally: ";
  cin >> AddNoiseToPointCloud;

  vector<Point3d> point_cloud_data_1;
  vector<Point3d> point_cloud_data_2;

//////////////////////////////////////////////////////////////////////////////////
  if(!PointCloudProcessing(argv[2], point_cloud_data_2)){
    return 0;
  }

  Eigen::MatrixXf dst(point_cloud_data_2.size(), 3);
  for(int i = 0; i<point_cloud_data_2.size(); i++){
    dst(i,0) = point_cloud_data_2[i].x;
    dst(i,1) = point_cloud_data_2[i].y;
    dst(i,2) = point_cloud_data_2[i].z;
  }
  
  ofstream outputFile3("/home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/ICP_TrICP/catkin_ws/src/ws/include/dst.xyz");
  for(int g = 0; g<dst.rows(); g++){
    for(int gh = 0; gh<3; gh++){
      outputFile3 << dst(g,gh) << " ";
    }
    outputFile3 << endl;
  }
  outputFile3.close();

///////////////////////////////////////////////////////////////////////////////
  if(!PointCloudProcessing(argv[1], point_cloud_data_1)){
    return 0;
  }
  Eigen::MatrixXf src(point_cloud_data_1.size(), 3);

  if(AddNoiseToPointCloud == 1){
    random_device rd; 
    normal_distribution<float> d (0,0.1);
    std::mt19937 gen(rd()); 
    float sample;
    cout << " Noise Added to the point cloud" << endl;
    for(int i = 0; i<point_cloud_data_1.size(); i++){
      sample = d(gen);
      src(i,0) = point_cloud_data_1[i].x+sample;
      src(i,1) = point_cloud_data_1[i].y+1+sample;
      src(i,2) = point_cloud_data_1[i].z+1+sample;
    }
  }  
  else{
    for(int i = 0; i<point_cloud_data_1.size(); i++){
      src(i,0) = point_cloud_data_1[i].x;
      src(i,1) = point_cloud_data_1[i].y;
      src(i,2) = point_cloud_data_1[i].z;
    }
  }


  ofstream outputFile("/home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/ICP_TrICP/catkin_ws/src/ws/include/src.xyz");
  for(int g = 0; g<src.rows(); g++){
    for(int gh = 0; gh<3; gh++){
      outputFile << src(g,gh) << " ";
    }
    outputFile << endl;
  }
  outputFile.close();

//////////////////////////////////////////////////////////////////////////////////
  Eigen::MatrixXf out(dst.rows(), 3);
  
  Eigen::MatrixXf Fuse(dst.rows(), 3);
  
  Fuse = fuse(src,dst);
  // cout << Fuse;
  ofstream myfile(OUTPUT_FILE_FUSE);
  for(int g = 0; g<Fuse.rows(); g++){
    for(int gh = 0; gh<3; gh++){
      myfile << Fuse(g,gh) << " ";
    }
    myfile << endl;
  }
  myfile.close();


  auto start = high_resolution_clock::now();

  if (CHOOSE == 1){
    iterative_closest_point(src, dst, out, MAX_ITERATIONS, ERROR_DROP_THRESH);
  }
  else if (CHOOSE == 2)
  {
    cout<<"Number of points to be trimmed from the Tr-iterative_closest_point: ";
    cin>>NUM_OF_TR_POINTS;  
    tr_iterative_closest_point(src, dst, out, MAX_ITERATIONS, ERROR_LOW_THRESH, DIST_DROP_THRESH, NUM_OF_TR_POINTS);
  }
  else
  {
    cout << "Invalid input nothing chosen to process the data";
    return 0;
  }
  
  auto stop = high_resolution_clock::now(); 
  auto duration = duration_cast<milliseconds>(stop - start);
  cout << "Finished in "+ to_string(duration.count()) +"ms and saved result into: " + OUTPUT_FILE << endl;
  // cout << out;
  // save the result into output file
  ofstream outputFile1(OUTPUT_FILE);
  for(int g = 0; g<src.rows(); g++){
    for(int gh = 0; gh<3; gh++){
      outputFile1 << out(g,gh) << " ";
    }
    outputFile1 << endl;
  }
  outputFile1.close();


  return 0;
}




void searchNN(const Eigen::MatrixXf & cloud1, const Eigen::MatrixXf & cloud2, const size_t k, Eigen::MatrixXi &indices, Eigen::MatrixXf &dists, const bool return_dist_squared = 0){
  const int max_leaf = 10;
  typedef Eigen::Matrix<float, Eigen::Dynamic, 3, Eigen::RowMajor> RowMatX3f;
  RowMatX3f coords1 = cloud1.leftCols(3);
  RowMatX3f coords2 = cloud2.leftCols(3);
  nanoflann::KDTreeEigenMatrixAdaptor<RowMatX3f> mat_index(3, coords1, max_leaf);
  mat_index.index->buildIndex();
  indices.resize(cloud2.rows(), k);
  dists.resize(cloud2.rows(), k);
  // do a knn search
  for (int i = 0; i < coords2.rows(); ++i) {
    // coords is RowMajor so coords.data()[i*3+0 / +1  / +2] represents the ith row of coords
    std::vector<float> query_pt{ coords2.data()[i*3+0], coords2.data()[i*3+1], coords2.data()[i*3+2] };

    std::vector<size_t> ret_indices(k);
    std::vector<float> out_dists_sqr(k);
    nanoflann::KNNResultSet<float> resultSet(k);
    resultSet.init(&ret_indices[0], &out_dists_sqr[0]);
    mat_index.index->findNeighbors(resultSet, &query_pt[0], nanoflann::SearchParams(10));
    for (size_t j = 0; j < k; ++j) {
        indices(i, j) = ret_indices[j];
        if(return_dist_squared){
          dists(i, j) = out_dists_sqr[j];
        }
        else{
          dists(i, j) = std::sqrt(out_dists_sqr[j]);
        }
    }
  }
}

int PointCloudProcessing(string file_path, vector<Point3d >& out_points){
  try{
    ifstream file(file_path);
    vector<Point3d > tmpv;
    Point3d tmp;

    double nx_ny_nz;
     
    while (file >> tmp.x && file >> tmp.y && file >> tmp.z && file >> nx_ny_nz && file >> nx_ny_nz && file >> nx_ny_nz){
      tmpv.push_back(tmp);
    }
    file.close();
    out_points = tmpv;
    return 1;
  }
  catch (const std::exception& e) {
    cout << "error opening the xyz file" << endl;
    return -1;
  } 
}

int EigenJacboiSVD(const Eigen::MatrixXd &A, const Eigen::MatrixXd &B, Eigen::Matrix3d &R, Eigen::Vector3d &t ){
    Eigen::Vector3d centroid_A(0,0,0);
    Eigen::Vector3d centroid_B(0,0,0);
    Eigen::MatrixXd AA = A;
    Eigen::MatrixXd BB = B;
    int row = A.rows();

    for(int i=0; i<row; i++){
        centroid_A += A.block<1,3>(i,0).transpose();
        centroid_B += B.block<1,3>(i,0).transpose();
    }
    centroid_A /= row;
    centroid_B /= row;
    for(int i=0; i<row; i++){
        AA.block<1,3>(i,0) = A.block<1,3>(i,0) - centroid_A.transpose();
        BB.block<1,3>(i,0) = B.block<1,3>(i,0) - centroid_B.transpose();
    }

    Eigen::MatrixXd H = AA.transpose()*BB;
    Eigen::MatrixXd U;
    Eigen::VectorXd S;
    Eigen::MatrixXd V;
    Eigen::MatrixXd Vt;

    Eigen::JacobiSVD<Eigen::MatrixXd> svd(H, Eigen::ComputeFullU | Eigen::ComputeFullV);
    U = svd.matrixU();
    S = svd.singularValues();
    V = svd.matrixV();
    Vt = V.transpose();

    R = Vt.transpose()*U.transpose();

    if (R.determinant() < 0 ){
        Vt.block<1,3>(2,0) *= -1;
        R = Vt.transpose()*U.transpose();
    }

    t = centroid_B - R*centroid_A;

    return 1;

}

int iterative_closest_point(const Eigen::MatrixXf &src, const Eigen::MatrixXf &dst, Eigen::MatrixXf &srcTransformation, const int max_itreations, const double error_drop_thresh){
  Eigen::MatrixXi indices;
  Eigen::MatrixXf dists;
  srcTransformation = src; 
  float prev_dist_sum = FLT_MAX;

  Eigen::MatrixXf src_neighbours(dst.rows(),3);
  double mean_error = 0;

  float dist_sum  = 0;
  for(int i=0; i<max_itreations; i++){
    searchNN(srcTransformation, dst, K, indices, dists);

    dist_sum = 0;
    for(int d=0; d<dists.size(); d++){
      dist_sum+=dists(d);
    }
    mean_error = dist_sum/dists.size();

    if(abs(mean_error) < iterative_closest_point_ERROR_LOW_THRESH){
      cout << "iterative_closest_point has sucessfully reached the neceserry error_low_thresh." << endl;
      return 1;
    }
    
    // reorder src to fit to the nearest neighbour scheme
    for(int j=0; j<src_neighbours.rows(); j++){
      int ind = indices(j,1);
      src_neighbours(j,0) = srcTransformation(ind,0);
      src_neighbours(j,1) = srcTransformation(ind,1);
      src_neighbours(j,2) = srcTransformation(ind,2);
    }

    // find transform matrix
    Eigen::Matrix3d tR;
    Eigen::Vector3d tt;
    EigenJacboiSVD(src_neighbours.cast <double> (), dst.cast <double> (), tR, tt);
    Eigen::Matrix3f R = tR.cast<float>();
    Eigen::Vector3f t = tt.cast<float>();

    // rotation
    srcTransformation = (R*srcTransformation.transpose()).transpose();

    // translation
    for(int fs = 0; fs<srcTransformation.rows();fs++){
      for(int a = 0; a<3; a++){
        srcTransformation(fs,a) = srcTransformation(fs,a)+t(a);   
      }
    }
//////////////////////////////////////////////////
    Eigen::MatrixXf a;
    a = dst.transpose()*srcTransformation;
    double sum = 0;
    for (int i=0; i<3; i++){
      sum += a(i,i);
    }
    double rotation_error_radians = atan((cos((sum-1)/2))* (180/3.14));
    cout << "***********************************************Rotation_Error_Radians: "<<rotation_error_radians<<endl;
///////////////////////////////////////////////////////////
    cout <<"iterative_closest_point Cycle "+ to_string(i)+ "*****" << endl;
    cout <<"MSE: "+ to_string(mean_error)+ "/" + to_string(iterative_closest_point_ERROR_LOW_THRESH)  <<endl;
    cout <<"Change of MSE: "+to_string(abs(previousError-mean_error))+ "/" + to_string(error_drop_thresh) << endl;


    previousError = mean_error;
    prev_dist_sum = dist_sum;
  }
}

void sort_matr(const Eigen::MatrixXf &m, 
               Eigen::MatrixXf &out, 
               Eigen::MatrixXi &indexes, 
               int to_save = -1){
  vector<pair<float, int> > vp;

  if(to_save == -1){
    to_save = m.rows();
  }

  for (int i = 0; i < m.rows(); i++) { 
    float vaaal = m(i);
    vp.push_back(make_pair(vaaal, i)); 
  }  

  std::stable_sort(vp.begin(), vp.end(),
                 [](const auto& a, const auto& b){return a.first < b.first;});

  Eigen::MatrixXi ind(to_save,1);
  Eigen::MatrixXf tmp_out(to_save,1);
  for (int i=0; i<to_save; i++){
    tmp_out(i,0)= m(vp[i].second);
    ind(i,0) = vp[i].second;
  }

  out = tmp_out;
  indexes = ind;
}


int tr_iterative_closest_point(const Eigen::MatrixXf &src,
           const Eigen::MatrixXf &dst,
           Eigen::MatrixXf &srcTransformation, 
           const int max_itreations,
           const double error_low_thresh, 
           const double dist_drop_thresh,
           const int Npo
           ){
  float prev_dist_sum = FLT_MAX;
  Eigen::MatrixXi knn_indices;
  Eigen::MatrixXf sq_dists, tr_sq_dists(Npo, 1);
  Eigen::MatrixXf tr_dst(Npo,3), tr_src(Npo, 3);
  srcTransformation = src; 

  Eigen::MatrixXf src_neighbours(dst.rows(),3);
  double mean_error = 0;

  for(int i=0; i<max_itreations; i++){
    searchNN(srcTransformation, dst, K, knn_indices, sq_dists, 1);


    Eigen::MatrixXi old_dst_ind;
    Eigen::MatrixXf sorted_tr_distances;
    sort_matr(sq_dists, sorted_tr_distances, old_dst_ind, Npo);
    
    for(int i =0; i<Npo; i++){
      int dst_ind = old_dst_ind(i);
      int src_ind = knn_indices(dst_ind,1);
      tr_src.block<1,3>(i,0) = srcTransformation.block<1,3>(src_ind,0);
      tr_dst.block<1,3>(i,0) = dst.block<1,3>(dst_ind,0);
    }

    float dist_sum = sq_dists.sum();  //sorted_tr_distances.sum();

    float e = dist_sum/Npo;
    if(e<error_low_thresh || abs(prev_dist_sum-dist_sum)<dist_drop_thresh){
      cout << "TR_iterative_closest_point has sucessfully reached the boundary conditions." << endl;
      return 1;
    }

    Eigen::Matrix3d tR;
    Eigen::Vector3d tt;
    EigenJacboiSVD(tr_src.cast<double>(), tr_dst.cast<double>(), tR, tt);
    Eigen::Matrix3f R = tR.cast<float>();
    Eigen::Vector3f t = tt.cast<float>();

    // rotation
    srcTransformation = (R*srcTransformation.transpose()).transpose();

    // translation
    for(int fs = 0; fs<srcTransformation.rows();fs++){
      for(int a = 0; a<3; a++){
        srcTransformation(fs,a) = srcTransformation(fs,a)+t(a);   
      }
    }
    
    cout <<"TR_iterative_closest_point Cycle "+ to_string(i)+ "*****" << endl;
    cout <<"trimmed MSE: "+ to_string(e)+ "/" + to_string(error_low_thresh) <<endl;
    cout <<"Change of trimmed MSE: "+to_string(abs(prev_dist_sum-dist_sum))+ "/" + to_string(dist_drop_thresh) << endl;


    prev_dist_sum = dist_sum;
  }
  
  return 1;
}

Eigen::MatrixXf fuse(const Eigen::MatrixXf &cloud1,const Eigen::MatrixXf &cloud2){
  Eigen::MatrixXf fused(cloud1.rows()+cloud2.rows(),cloud1.cols());
  fused << cloud1,cloud2;

  std::vector<Eigen::VectorXf> vec;

  for (int i = 0;i<fused.rows();++i){
    vec.push_back(fused.row(i));
  } 
  std::sort(vec.begin(),vec.end(),[](Eigen::VectorXf const& t1, Eigen::VectorXf const& t2){return t1(0)<t2(0);});
  auto it = std::unique(vec.begin(),vec.end());
  vec.resize(std::distance(vec.begin(),it));
  fused.resize(vec.size(),3);
  for (int i=0;i<vec.size();++i){
    fused.row(i)=vec[i];
  }
  return fused;
}





