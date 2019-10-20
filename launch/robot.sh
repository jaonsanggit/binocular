#!/bin/zsh

cd ~/catkin_ws/launch

echo "starting roscore ..."
gnome-terminal -x bash -c "zsh ./core.sh; exec bash;"
sleep 3

echo "starting serialport ..."
gnome-terminal -x bash -c "zsh ./eyes.sh; exec bash;"
sleep 3

echo "starting  proxy ..."
gnome-terminal -x bash -c "zsh ./proxy.sh; exec bash;"
sleep 3

echo "starting npm ..."
gnome-terminal -x bash -c "zsh ./website.sh; exec bash;"
sleep 10

echo "starting  chrome ..."
gnome-terminal -x bash -c "zsh ./chrome.sh; exec bash;"
sleep 60

