# 3D-Sensing-Sensor-Fusion
Stereo Matching code implementation in Naive and Dynamic Based approach. 

In the following sections you can see the 2 input images given to the code and the respective output of Naive based approach, dynamic program based approach & 3D point cloud.

Except  "Art" and "Book Shelf" section  rest of the 3D point clouds are based on "Binocular Stereo" which results in the concentration of the 3D points near to the focus and as a result you see that points spread out from the center of the image outwards. Where as the 3D point cloud of Art and Book Shelf sections are normal one and you can easily distingush it, as it looks as if its in real life scene. 


#
# Art

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Art/Art/view0.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Art/Art/view1.png" width="400" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Art/Naive/stero_matching_naive.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Art/DP/stero_matching_dynamic_program.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Art/Naive/snapshot000.png" width="400" >
#
# Book Shelf 

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Books/Books/view0.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Books/Books/view1.png" width="400" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Books/Naive/stero_matching_naive.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Books/DP/stero_matching_dynamic_program.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Books/Naive/snapshot00.png" width="400" >

#
# Plant

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Aloe/Aloe/view1.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Aloe/Aloe/view5.png" width="400" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Aloe/Naive/stero_matching_naive.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Aloe/DP/stero_matching_dynamic_program.png" width="400"><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Aloe/Naive/snapshot000.png" width="400" >
#
# Baby

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Baby/Baby1/view1.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Baby/Baby1/view5.png" width="400" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Baby/Naive/stero_matching_naive.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Baby/DP/stero_matching_dynamic_program.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Baby/Naive/snapshot000.png" width="400" >

#
# Bowling Ball

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Bowling/Bowling1/view1.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Bowling/Bowling1/view5.png" width="400" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Bowling/Naive/stero_matching_naive.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Bowling/DP/stero_matching_dynamic_program.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Bowling/Naive/snapshot000.png" width="400" >

#
# Cloth

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Cloth/Cloth1/view1.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Cloth/Cloth1/view5.png" width="400" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Cloth1/Naive/stero_matching_naive.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Cloth1/DP/stero_matching_dynamic_program.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Cloth1/Naive/snapshot000.png" width="400" >

#
# Flower Pot
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Flowerpots/Flowerpots/view1.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Flowerpots/Flowerpots/view5.png" width="400" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Flowerpots/Naive/stero_matching_naive.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Flowerpots/DP/stero_matching_dynamic_program.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Flowerpots/Naive/snapshot000.png" width="400" >
#
# Rocks

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Rocks1/Rocks1/view1.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Input_Images/Rocks1/Rocks1/view5.png" width="400" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Rocks/Naive/stero_matching_naive.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Rocks/DP/stero_matching_dynamic_program.png" width="400" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Rocks/Naive/snapshot000.png" width="400" >
#


In order to execute the code please follow the commands given below.
```
$ catkin_create_pkg ws std_msgs rospy roscpp 
```
Then git clone this repo in the worspace and then execute the following commands in the parent package which you crreated using the above command.
```
$ catkin_make
$ source devel/setup.bash
```
To run the code use the following command. (Note: As this is specific to my workstation please make sure you provide the correct paths)

```
$ rosrun ws OpenCV_naive_stereo /home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/3dssf/src/ws/data/im0.pgm /home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/3dssf/src/ws/data/im1.pgm /home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/3dssf/src/ws/include/ws/ /home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/3dssf/src/ws/include/ws/ 

```
#
# Evaluation Metrics
#

Evaluation Metrics of the disparity naive approach based images to the ground truth disparity images.

As you can see the "Cloth" SSMI seems pretty good as it close to the ground truth. Whereas in case of other images there are some freckles in the disparity image obtained.


The another trend that I have noticed is that the dynamic programming takes a quite longer time then the naive based approach. I believe the reason behind this is because of back-tracking of the optimal path to find the disparity map and also the computation cost for the calculating the cost map and path matrices.

In my case the point cloud computation for the dynamic programming based approach is faster compared to the naive based approach. 





| Image       | Naive       |     DP     | 3D POint Cloud | SSMI | Mean Squared Error | PSNR |
| ----------- | ----------- | ---------- | -------------- | ---- | ------------------ | ---- |
|    Art   |  2126.78s   |   4949.74s   |   5.22s & 5.26s  |  0.595    |       37.689            |    14.236 |
|      Book Shelf       |    2031.67s   |   4939.43s |  6.89s & 4.77 s  |  0.679091    |    20.3181  |  35.052    |
|    Plant      |   207.42s   |   889.98s   |    1.86s & 1.51s  |  0.754759    |     15.1779  |  36.3187    |
|   Baby     |    151.81s  | 339.60s     | 1.57s & 0.81s   |   0.772008   |       5.46483             |   40.755  |
| Bowling Ball    |    155.02s  | 343.14s     | 1.61s & 0.62s   |   0.7568   |   13.7633    |    36.7436  |
| Cloth    |    118.20s     |     290.51s  |       1.10s & 0.66s  | 0.956163     |  11.4855  |  37.5293    |
|   Flower Pot    |  130.10s  |    334.07s | 1.64s & 0.36s      |    0.770409 |      28.8182    | 33.5341|
| Rocks     |    122.75s         |   313.15s         |    1.66s & 0.87s            |  0.875    |      18.6975   |  35.413    |

#
### X-Image : Y-SSIM : Z-Mean Squared Error
#
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Screenshot%20from%202021-11-17%2020-45-13.png" width="500" class="center">

#
### X-Image : Y-SSIM : Z-PSNR
#
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Output_Images/Screenshot%20from%202021-11-17%2020-45-23.png" width="500" class="center" >

#
# Note
Please make sure that you input the corect image to the evaluation metrics functioin code present in "main.cpp", and for now I am setting it to accept the input images that you provide.
#
