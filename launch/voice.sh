#!/bin/zsh

cd ~/catkin_ws/launch

echo "voice_front starting ... "
gnome-terminal -x bash -c "zsh ./voice_front.sh; exec bash;"
echo "voice_front start complete."
sleep 1

echo "voice_aiui starting ..."
gnome-terminal -x bash -c "zsh ./voice_aiui.sh; exec bash;"
echo "voice_aiui start complete"
sleep 1

source /opt/ros/kinetic/setup.zsh
source ~/catkin_ws/devel/setup.zsh

rosrun communication dataTransfer
