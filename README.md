# BEEMIC - Human-inspired drone movement control
<img src="https://github.com/bickelmps/BEEMIC/blob/master/figures/logo.PNG" width="240" height="100">

#### Give your drone the characteristics of your choice!

------------------------------------------------
Produced in < 24h, WORK IN PROGRESS

------------------------------------------------
###### Team Beemic
Förderer, N. [@NicolajFoerderer](https://github.com/NicolajFoerderer); Omanovic, A.; Anschau Schwarzer, K. [@kevinanschau](https://github.com/kevinanschau); Bickel, V. T. [@bickelmps](https://github.com/bickelmps)
###### An ETH Zurich PolyHack 2018 Project
<img src="https://github.com/bickelmps/BEEMIC/blob/master/figures/logopoly.png?raw=true" width="250" height="60">

##### MIT License - Copyright (c) 2018 Team BEEMIC, ETH Zurich
Please refer to this routine as:
#### Förderer, N.; Omanovic, A.; Anschau Schwarzer, K.; Bickel, V. T. BEEMIC - Human-inspired drone movement control. 2018.
--------------------------------------------------

## Dependencies

We use [Openpose](https://github.com/CMU-Perceptual-Computing-Lab/openpose) to extract human(-like) postures and movement patterns from multiple-view videos, using only smartphone cameras.


<img src="https://github.com/bickelmps/BEEMIC/blob/master/figures/openpose_hulk.gif?raw=true" width="300" height="300">

Human movement patterns are translated to machine-applicable patterns. Trained drone behavior is simulated in [Gazebo](http://gazebosim.org/), controlling the drone through [Dronecode](https://www.dronecode.org/sdk/) with [px4](http://px4.io/) as backend.


## Installation

Copy this repository into the `DronecodeSDK/examples` folder. Build and make:

```
mkdir build && cd build
cmake ..
make
```

## Usage

We extract pose information from videos with [Openpose](https://github.com/CMU-Perceptual-Computing-Lab/openpose).

```
bin/OpenPoseDemo.exe --video examples/media/<video_name>.avi --write_video output/<output_name>.avi --write_json output//
```

Add characteristics to a general trajectory of your choice from the generated poses.
```
python add_characteristic.py
```

Start the Gazebo simulation with

```
make posix_sitl_default gazebo
```

Follow the trajectory with a vanilla velocity controller
```
./beemic_vel <filename.txt>
```

## Possible Results

A happy & jumping/dancing person; after filming and translation expressed by the drone as:

<img src="https://github.com/bickelmps/BEEMIC/blob/master/figures/happy_drone.gif?raw=true" width="300" height="400">

------------------
##### MIT License - Copyright (c) 2018 Team BEEMIC, ETH Zurich
