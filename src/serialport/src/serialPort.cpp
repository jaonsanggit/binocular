#include <ros/ros.h> 
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <std_msgs/String.h> 
#include <std_msgs/Empty.h> 
#include "serialport/CJsonObject.hpp"
#include "serialport/robot.h"

int main (int argc, char** argv) 
{ 
      //初始化节点 
      ros::init(argc, argv, "serialport"); 
      //声明节点句柄 
      ros::NodeHandle nh; 

      std::string path("/home/sanghongrui/catkin_ws/src/serialport/src/face.json");
      std::ifstream t(path); //读文件ifstream,写文件ofstream，可读可写fstream
      if(!t) ROS_ERROR_STREAM("Unable to open JSON file"); 
      std::stringstream buffer;
      buffer << t.rdbuf();
      std::string str_json = buffer.str();

      neb::CJsonObject oJson(str_json);
      int fTestValue = 0;
      std::cout << "location: ";
      for (int i = 0; i < oJson[0]["location"].GetArraySize(); ++i)
      {
            oJson[0]["location"].Get(i, fTestValue);
            std::cout <<  fTestValue << '\t';
      }
      std::cout << std::endl;

      ROBOTEYES robot;  // open port & initialize robot;

      ros::Rate loop_rate(1); 
      while(ros::ok()) 
      { 
        ros::spinOnce(); 
        loop_rate.sleep(); 
      } 

      return 0;
}