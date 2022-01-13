##
# Iterative Closest Point

Iterative closest point (ICP)is an algorithm employed to minimize the difference between two clouds of points. ICP is often used to reconstruct 2D or 3D surfaces from different scans, to localize robots and achieve optimal path planning (especially when wheel odometry is unreliable due to slippery terrain)

```
.
├── CMakeLists.txt -> /opt/ros/melodic/share/catkin/cmake/toplevel.cmake
└── ws
    ├── CMakeLists.txt
    ├── include
    │   ├── dst.xyz
    │   ├── fuse.xyz
    │   ├── OutputImages
    │   │   ├── Armdillo1.png
    │   │   ├── Armdillo2.png
    │   │   ├── Armdillo3.png
    │   │   ├── Armdillo4.png
    │   │   ├── Armdillo5.png
    │   │   ├── bunny1.png
    │   │   ├── bunny2.png
    │   │   ├── bunny3.png
    │   │   ├── Fountain1.png
    │   │   ├── Fountain2.png
    │   │   └── Fountain3.png
    │   ├── output.xyz
    │   ├── src.xyz
    │   └── ws
    │       └── nanoflann.hpp
    ├── package.xml
    └── src
        ├── Armadillo_rotated.xyz
        ├── Armadillo_sparse.xyz
        ├── bunny_rotated.xyz
        ├── bunny_sparse.xyz
        ├── code.cpp
        ├── nanoflann.hpp
        ├── pointCloud1.xyz
        └── pointCloud2.xyz

5 directories, 27 files
```
##
# Armdillo

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/ICP_TrICP/catkin_ws/src/ws/include/OutputImages/Armdillo1.png" width="400" ><figcaption>Fig.1 -The Original & Rotated Armdillo point cloud</figcaption>

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/ICP_TrICP/catkin_ws/src/ws/include/OutputImages/Armdillo2.png" width="400" >
<figcaption>Fig.2 -The output Armdillo point cloud from ICP</figcaption>

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/ICP_TrICP/catkin_ws/src/ws/include/OutputImages/Armdillo3.png" width="400" >
<figcaption>Fig.3 -The output Armdillo point cloud & the destination point cloud from ICP</figcaption>

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/ICP_TrICP/catkin_ws/src/ws/include/OutputImages/Armdillo5.png" width="400" >
<figcaption>Fig.4 -The output Armdillo point cloud & the destination point cloud from Tr-ICP</figcaption>

##
# Bunny


<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/ICP_TrICP/catkin_ws/src/ws/include/OutputImages/bunny1.png" width="400" >
<figcaption>Fig.5 -The Original & Rotated Bunny point cloud</figcaption>

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/ICP_TrICP/catkin_ws/src/ws/include/OutputImages/bunny2.png" width="400" >
<figcaption>Fig.6 -The output Bunny point cloud from ICP</figcaption>


<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/ICP_TrICP/catkin_ws/src/ws/include/OutputImages/bunny3.png" width="400" >
<figcaption>Fig.7 -The output Bunny point cloud & the destination point cloud from ICP with less iteration to show that its working</figcaption>

##
# Fountain

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/ICP_TrICP/catkin_ws/src/ws/include/OutputImages/Fountain3.png" width="400" >
<figcaption>Fig.8 -The Fountain point cloud added noise </figcaption>

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/ICP_TrICP/catkin_ws/src/ws/include/OutputImages/Fountain1.png" width="400" >
<figcaption>Fig.9 -The output Fountain point cloud from ICP</figcaption>

<img src="https://github.com/omkarbhoite25/3D-Sensing-Sensor-Fusion/blob/main/ICP_TrICP/catkin_ws/src/ws/include/OutputImages/Fountain2.png" width="400" >
<figcaption>Fig.10 -The output Fountain point cloud after complete 3D-Reconstruction</figcaption>



##



|Image|Runtime| ICP/Tr-ICP|
|-----|-------|-----------|
|Fountain|271724ms|ICP |
|Fountain|8192ms|Tr-ICP|
|Armadillo|8659ms|ICP|
|Armadillo|1105ms|Tr-ICP|
|Bunny|1495ms|ICP|
|Bunny|701ms|Tr-ICP|
|Fountain|122435ms|ICP (With Noise)|



|Image|Error Radians|
|-----|-------------|
|Bunny|(0.935667-0.939346-0.941136-0.942157-0.942893-0.943415-0.943801-0.9441-0.944246-0.944326-0.944296-0.944076)|