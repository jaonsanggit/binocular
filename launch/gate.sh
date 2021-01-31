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

echo "starting voice..."
gnome-terminal -x bash -c "zsh ./gate_voice.sh; exec bash;"
sleep 5

#echo "starting npm ..."
#gnome-terminal -x bash -c "zsh ./website.sh; exec bash;"
#sleep 5

#echo "starting voice all ..."
#gnome-terminal -x bash -c "zsh ~/kevin.sh; exec bash;"
#sleep 10

#echo "123" | sudo -S systemctl stop supervisor.service
#sleep 5

#echo "starting  chrome ..."
#gnome-terminal -x bash -c "zsh ./firefox.sh; exec bash;"
#sleep 5
