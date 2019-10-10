#include <ros/ros.h> 
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <std_msgs/String.h> 
#include <std_msgs/Empty.h> 
#include <ros_cv_proxy/FaceTarget.h>
#include "serialport/CJsonObject.hpp"
#include "serialport/robot.h"

static ROBOTEYES robot;  // open port & initialize robot;
static int target_w = 960;
static int target_h = 540;
void coreCallback(const ros_cv_proxy::FaceTarget::ConstPtr& msg)
{
      target_w = int(msg->target.x);
      target_h = int(msg->target.y);
      robot.Turn(target_w, target_h);
      // std::cout << target_w << ' ' << target_h << std::endl;
}

int main (int argc, char** argv) 
{ 
      //初始化节点 
      ros::init(argc, argv, "serialport"); 
      //声明节点句柄 
      ros::NodeHandle nh; 

      ros::Subscriber sub = nh.subscribe("custom_chatter", 2, coreCallback);

      // std::string path("/home/sanghongrui/catkin_ws/src/serialport/src/face.json");
      // std::ifstream t(path); //读文件ifstream,写文件ofstream，可读可写fstream
      // if(!t) ROS_ERROR_STREAM("Unable to open JSON file"); 
      // std::stringstream buffer;
      // buffer << t.rdbuf();
      // std::string str_json = buffer.str();

      // neb::CJsonObject oJson(str_json);
      // int fTestValue = 0;
      // std::cout << "location: ";
      // for (int i = 0; i < oJson[0]["location"].GetArraySize(); ++i)
      // {
      //       oJson[0]["location"].Get(i, fTestValue);
      //       std::cout <<  fTestValue << '\t';
      // }
      // std::cout << std::endl;

      ros::Rate loop_rate(100); 
      while(ros::ok()) 
      { 
            ros::spinOnce(); 
            loop_rate.sleep(); 
      } 

      return 0;
}