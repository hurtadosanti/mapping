# Go chase it!
In this project, we create a simulated robot using Gazebo and Ros that can chase a white ball.

## Dependencies
- Ubuntu 16.04
- ROS Kinetic Kame
## Installation
- Create a workspace

        mkdir -p catkin_ws/src
        cd catkin_ws/src

- Clone this repository on the src folder location
  
        git clone git@github.com:hurtadosanti/go_chase_it.git ./

- Initialize workspace
  
        catkin_init_workspace

- Build
  
        cd ..
        catkin_make
## Execution

- Run the main program in a terminal with X support
  
        cd catkin_ws
        source devel/setup.bash
        roslaunch my_robot world.launch

- On a different terminal run the nodes
  
        cd catkin_ws
        source devel/setup.bash
        roslaunch ball_chaser ball_chaser.launch

## License
MIT License Copyright (c) 2020 Santiago Hurtado
