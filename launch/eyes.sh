#!/bin/zsh

source /opt/ros/kinetic/setup.zsh
source ~/catkin_ws/devel/setup.zsh
echo 123 | sudo -S chmod 666 /dev/ttyUSB0
rosrun serialport serialport
