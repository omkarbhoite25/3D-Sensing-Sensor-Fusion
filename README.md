# 3D-Sensing-Sensor-Fusion

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/outputImages/stero_matching_naive1.png" width="300" > 
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/outputImages/stero_matching_naive2.png" width="300" >

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/outputImages/stero_matching_dynamic_program1.png" width="300" >
<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/outputImages/stero_matching_dynamic_program2.png" width="300" >


```
$ catkin_create_pkg ws std_msgs rospy roscpp 
$ source devel/setup.bash
```

```
$ rosrun ws OpenCV_naive_stereo /home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/3dssf/src/ws/data/im0.pgm /home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/3dssf/src/ws/data/im1.pgm /home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/3dssf/src/ws/include/ws/ /home/omkar/ELTE/ELTE/3DSSF/3D-Sensing-Sensor-Fusion/3dssf/src/ws/include/ws/ 

```

