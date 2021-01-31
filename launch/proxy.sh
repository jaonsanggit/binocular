#!/bin/zsh

source ~/.venv/bin/activate 
source /opt/ros/kinetic/setup.zsh
source ~/catkin_ws/devel/setup.zsh

#rosrun ros_cv_proxy proxy_raw.py
rosrun ros_cv_proxy rosTalker.py
#rosrun ros_cv_proxy guardTalker.py
