#!/bin/zsh

sleep 5 
echo "starting computer..."

cd ~/catkin_ws/launch
echo "starting roscore ..."
gnome-terminal -x bash -c "zsh ./core.sh; exec bash;"
sleep 5

echo "starting serialport ..."
gnome-terminal -x bash -c "zsh ./eyes.sh; exec bash;"
sleep 5

echo "starting  proxy ..."
gnome-terminal -x bash -c "zsh ./proxy.sh; exec bash;"
sleep 5


echo "starting npm ..."
gnome-terminal -x bash -c "zsh ./website.sh; exec bash;"
sleep 20

echo "starting  chrome ..."
gnome-terminal -x bash -c "zsh ./firefox.sh; exec bash;"
sleep 5

echo "starting voice all ..."
gnome-terminal -x bash -c "zsh ./voice.sh; exec bash;"
