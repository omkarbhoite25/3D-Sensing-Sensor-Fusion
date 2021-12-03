#
# Note: I have commented a lot of stuff in the code and one needs to tweak it, and also provide with correct paths to images for further use.

# Bilateral Filter

Using the **Bilaterlateral** filter create an image matrix where the spectral and spatial sigma varies along the row [1 10 30 50] and along the column as [1 10 30 50]. So, diagonally we have the sigma's as [(1,1),(10,10,),(30,30),(50,50)] and the rest as easy to figure out.

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_1_1.png" width="200" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_1_10.png" width="200" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_1_30.png" width="200" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_1_50.png" width="200" >

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_10_1.png" width="200" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_10_10.png" width="200" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_10_30.png" width="200" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_10_50.png" width="200" >


<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_30_1.png" width="200" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_30_10.png" width="200" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_30_30.png" width="200" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_30_50.png" width="200" >

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_50_1.png" width="200" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_50_10.png" width="200" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_50_30.png" width="200" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/bilateral/Bilateral_Filter_50_50.png" width="200" >






#
# Upsampling Guided Joint Bilaterl Filter




In the image matrix below the spatial & spectral sigma are varied from 1 to 5 along the row and columns.
This is just the sample out all the 12 different pairs of RGB and Depth images. 

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_1_1.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_1_2.png" width="175" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_1_3.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_1_4.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_1_5.png" width="175" >

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_2_1.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_2_2.png" width="175" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_2_3.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_2_4.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_2_5.png" width="175" >



<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_3_1.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_3_2.png" width="175" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_3_3.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_3_4.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_3_5.png" width="175" >



<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_4_1.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_4_2.png" width="175" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_4_3.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_4_4.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_4_5.png" width="175" >



<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_5_1.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_5_2.png" width="175" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_5_3.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_5_4.png" width="175" ><img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_5_5.png" width="175" >

#
# Noise (Synthetic depth and noise generator)

The image to the lef is downsampled and then random noise is being added to the image. This image is then used as the input image for the upsampling guided joint bilateral filter.

The image to the right is when is applied with the upsampled guided joint bilateral filter

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Down_Sampled_With_Noise.png" width="450" > <img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/output%20cones/Joint_Bilateral_Filter_5_5.png" width="450" >

#
# My own depth generated images
The image to the lef is downsampled and then random noise is being added to the image. This image is then used as the input image for the upsampling guided joint bilateral filter.

The image to the right is when is applied with the upsampled guided joint bilateral filter, the output is not as good as expected here and the spectral sigma is 0.2 and spatial sigma is 0.5, But I presume that its just the play of sigma's that can lead to better output images.

Also, lot of other out images with different sigmas can be found in the directory. This is just the sample from it.

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/my%20own%20dataset/Down_Sampled_With_Noise.png" width="450" > <img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/Filters/filter/catkin/src/beginner_tutorials/include/beginner_tutorials/my%20own%20dataset/Joint_Bilateral_Filter_3_0.2_0.5.png" width="450" >



#
# Evaluation

Generated output images for the upsampled guided joint bilateral filter for 12 different pair of RGB and Depth images but only few were used to perform the SSMI and PSNR Evaluation and the result is shown below.

|Filter|Runtime|
|------|-------|
|Bilateral|0.33-0.33 sec|
|Upsampling Guided Joint Bilateral|0.44-0.66 sec|


Structural Similarity Index (Spectral Sigma = 5, Spatial Sigma = 5)

| Images   |      Upsampling Guided Joint Bilateral Filter      |  Upsampling bilinear Interpolation | 
|----------|:--------------------------------------------------:|-----------------------------------:|
|Gifts|0.961224|0.961118|
|Aloe|0.890084|0.889586|
|Baby|0.928602|0.928214|
|Books|0.966113|0.965952|
|Reindeer|0.959755|0.96304|
|Cleaning Equipmemnt|0.952163|0.951438|

PSNR (Spectral Sigma = 5, Spatial Sigma = 5)

| Images   |      Upsampling Guided Joint Bilateral Filter      |  Upsampling bilinear Interpolation | 
|----------|:--------------------------------------------------:|-----------------------------------:|
|Gifts|26.3936|25.9904|
|Aloe|30.545|25.6993|
|Baby|28.7898|28.927|
|Books|28.5899|25.1427|
|Reindeer|27.4775|27.0694|
|Cleaning Equipmemnt|27.1574|26.8003|

#

Note: Joint_Bilateral_Filter_23_23.png means that its an image output from guided upsampled joint bilateral filter with spectral sigma = 23 and spatial sigma = 23
There are lots of images with diferent spectral and spatial sigma's and can be viewed in the following directories.
If a image has **bl** ints name then is **bi-linear interpolated** and if it has **cu** then is **cubic interpolated**
Below is the tree structure of the main directory and you can seem where the diffenet image are located.

#

```
.
├── beginner_tutorials
│   ├── CMakeLists.txt
│   ├── include
│   │   ├── beginner_tutorials  <-------- The output images of Upsampling Guided Joint Bilateral Filter and its Evaluation images too.
│   │   │   ├── bilateral
│   │   │   │   ├── Bilateral_Filter_10_10.png
│   │   │   │   ├── Bilateral_Filter_10_1.png
│   │   │   │   ├── Bilateral_Filter_10_30.png
│   │   │   │   ├── Bilateral_Filter_10_50.png
│   │   │   │   ├── Bilateral_Filter_1_10.png
│   │   │   │   ├── Bilateral_Filter_1_1.png
│   │   │   │   ├── Bilateral_Filter_1_30.png
│   │   │   │   ├── Bilateral_Filter_1_50.png
│   │   │   │   ├── Bilateral_Filter_30_10.png
│   │   │   │   ├── Bilateral_Filter_30_1.png
│   │   │   │   ├── Bilateral_Filter_30_30.png
│   │   │   │   ├── Bilateral_Filter_30_50.png
│   │   │   │   ├── Bilateral_Filter_50_10.png
│   │   │   │   ├── Bilateral_Filter_50_1.png
│   │   │   │   ├── Bilateral_Filter_50_30.png
│   │   │   │   └── Bilateral_Filter_50_50.png
│   │   │   ├── Down_Sampled_With_Noise.png
│   │   │   ├── Joint_Bilateral_Filter.png
│   │   │   ├── my own dataset
│   │   │   │   ├── Down_Sampled_With_Noise.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_0.2_0.5.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_0.2_0.7.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_2_50.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_50_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_5.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_7.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_5.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_7.png
│   │   │   │   ├── Joint_Bilateral_Filter_7_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_7_5.png
│   │   │   │   └── Joint_Bilateral_Filter_7_7.png
│   │   │   ├── Original_Image.png
│   │   │   ├── output aloe
│   │   │   │   ├── disp1.png
│   │   │   │   ├── Down_Sampled_With_Noise.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_4.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_5.png
│   │   │   │   ├── Joint_Bilateral_Filter_bl_5_5.png
│   │   │   │   └── Joint_Bilateral_Filter_cu_5_5.png
│   │   │   ├── output art
│   │   │   │   ├── Down_Sampled_With_Noise.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_23_23.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_4.png
│   │   │   │   └── Joint_Bilateral_Filter_5_5.png
│   │   │   ├── output baby
│   │   │   │   ├── disp1.png
│   │   │   │   ├── Down_Sampled_With_Noise.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_23_23.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_4.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_5.png
│   │   │   │   ├── Joint_Bilateral_Filter_bl_5_5.png
│   │   │   │   └── Joint_Bilateral_Filter_cu_5_5.png
│   │   │   ├── output book
│   │   │   │   ├── disp1.png
│   │   │   │   ├── Down_Sampled_With_Noise.png
│   │   │   │   ├── Joint_Bilateral_Filter_10_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_10.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_4.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_5.png
│   │   │   │   ├── Joint_Bilateral_Filter_bl_5_5.png
│   │   │   │   └── Joint_Bilateral_Filter_cu_5_5.png
│   │   │   ├── output bowling
│   │   │   │   ├── Down_Sampled_With_Noise.png
│   │   │   │   ├── Joint_Bilateral_Filter_10_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_10.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_4.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_5.png
│   │   │   │   └── Joint_Bilateral_Filter_bl_5_5.png
│   │   │   ├── output cloth
│   │   │   │   ├── Down_Sampled_With_Noise.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_4.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_5.png
│   │   │   │   └── Joint_Bilateral_Filter_bl_5_5.png
│   │   │   ├── output cones
│   │   │   │   ├── Down_Sampled_With_Noise.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_4.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_5.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_4.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_5.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_4.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_5.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_4.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_5.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_4.png
│   │   │   │   └── Joint_Bilateral_Filter_5_5.png
│   │   │   ├── output flowerpots
│   │   │   │   ├── Down_Sampled_With_Noise.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_4.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_5.png
│   │   │   │   ├── Joint_Bilateral_Filter_bl_5_5.png
│   │   │   │   └── Joint_Bilateral_Filter_nn_5_5.png
│   │   │   ├── output gifts
│   │   │   │   ├── disp1.png
│   │   │   │   ├── Down_Sampled_With_Noise.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_4.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_5.png
│   │   │   │   ├── Joint_Bilateral_Filter_bl_5_5.png
│   │   │   │   └── Joint_Bilateral_Filter_cu_5_5.png
│   │   │   ├── output reindeer
│   │   │   │   ├── disp1.png
│   │   │   │   ├── Down_Sampled_With_Noise.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_4.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_5.png
│   │   │   │   ├── Joint_Bilateral_Filter_bl_5_5.png
│   │   │   │   └── Joint_Bilateral_Filter_cu_5_5.png
│   │   │   ├── output rocks
│   │   │   │   ├── Down_Sampled_With_Noise.png
│   │   │   │   ├── Joint_Bilateral_Filter_1_1.png
│   │   │   │   ├── Joint_Bilateral_Filter_2_2.png
│   │   │   │   ├── Joint_Bilateral_Filter_3_3.png
│   │   │   │   ├── Joint_Bilateral_Filter_4_4.png
│   │   │   │   ├── Joint_Bilateral_Filter_5_5.png
│   │   │   │   └── Joint_Bilateral_Filter_bl_5_5.png
│   │   │   └── output room
│   │   │       ├── disp1.png
│   │   │       ├── Down_Sampled_With_Noise.png
│   │   │       ├── Joint_Bilateral_Filter_1_1.png
│   │   │       ├── Joint_Bilateral_Filter_2_2.png
│   │   │       ├── Joint_Bilateral_Filter_3_3.png
│   │   │       ├── Joint_Bilateral_Filter_4_4.png
│   │   │       ├── Joint_Bilateral_Filter_5_5.png
│   │   │       ├── Joint_Bilateral_Filter_bl_5_5.png
│   │   │       └── Joint_Bilateral_Filter_cu_5_5.png
│   │   ├── lena.png
│   │   └── output bilateral filter <---------------- The output images of the bilateral filter
│   │       ├── Bilateral_Filter_100_10.png
│   │       ├── Bilateral_Filter_10_15.png
│   │       ├── Bilateral_Filter_10_18.png
│   │       ├── Bilateral_Filter_10_23.png
│   │       ├── Bilateral_Filter_1_1.png
│   │       ├── Bilateral_Filter_1_2.png
│   │       ├── Bilateral_Filter_1_3.png
│   │       ├── Bilateral_Filter_1_4.png
│   │       ├── Bilateral_Filter_2_1.png
│   │       ├── Bilateral_Filter_2_2.png
│   │       ├── Bilateral_Filter_23_43.png
│   │       ├── Bilateral_Filter_2_3.png
│   │       ├── Bilateral_Filter_2_4.png
│   │       ├── Bilateral_Filter_2_50.png
│   │       ├── Bilateral_Filter_3_1.png
│   │       ├── Bilateral_Filter_3_2.png
│   │       ├── Bilateral_Filter_3_3.png
│   │       ├── Bilateral_Filter_3_4.png
│   │       ├── Bilateral_Filter_4_1.png
│   │       ├── Bilateral_Filter_4_2.png
│   │       ├── Bilateral_Filter_4_3.png
│   │       ├── Bilateral_Filter_4_4.png
│   │       ├── Bilateral_Filter_50_2.png
│   │       ├── Bilateral_Filter_70_75.png
│   │       └── Original_Image.png
│   ├── package.xml
│   └── src
│       └── main.cpp
└── CMakeLists.txt -> /opt/ros/melodic/share/catkin/cmake/toplevel.cmake


```
