
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
