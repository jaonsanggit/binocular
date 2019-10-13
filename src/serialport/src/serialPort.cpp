#include <ros/ros.h> 
#include <string>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
// #include <fstream>
// #include <sstream>
#include <std_msgs/String.h> 
#include <std_msgs/Empty.h> 
#include <msgfile/FaceTarget.h>
// #include "serialport/CJsonObject.hpp"
#include "serialport/robot.h"

static ROBOTEYES robot;  // open port & initialize robot;
static int target_w = 960;
static int target_h = 540;

static struct timeval start = {0, 0};

void coreCallback(const msgfile::FaceTarget::ConstPtr& msg)
{
      static std::vector<std::pair<int,int>> target_vec;
      static struct timeval initTime = {0, 0};

      gettimeofday(&start,NULL); 

      if (msg->cmd == "idle") {
            ROS_INFO("\n--------------IDLE------------------"); 
            ROS_INFO("  Receive idle status."); 
            robot.idleActInit();
            ROS_INFO("  Eyes idleAct.");
            return ;
      }

      else if (msg->header.frame_id != "core") {
            ROS_INFO("\n-------------NOT CORE-------------------");             
            ROS_INFO("  Receive msg but not from core."); 
            return ;            
      }

      else if (msg->cmd == "init") {
            ROS_INFO("------------INIT--------------------");
      }

      // if (!target_vec.empty()) {
      //       init_Action(target_vec, 500);
      //       target_w = target_vec.front().first;
      //       target_h = target_vec.front().second;
      //       target_vec          
      // }
      else {
            // std::vector<uint8_t> name = msg->user_name;
            ROS_INFO("--------------WORKING------------------"); 
      }

      target_w = int(msg->target.x);
      target_h = int(msg->target.y);
      std::cout << "  frame_id: " << msg->header.frame_id << std::endl;
      setlocale(LC_CTYPE, "zh_CN.utf8");
      std::cout << "  user_name: " << msg->name << std::endl;
      std::cout << "  target_w: " << target_w << '\t' 
                << "  target_h: " << target_h 
                << std::endl << std::endl; 

      robot.Turn(target_w, target_h);
      // std::cout << target_w << ' ' << target_h << std::endl;
}

int main (int argc, char** argv) 
{ 
      //初始化节点 
      ros::init(argc, argv, "serialport"); 
      //声明节点句柄 
      ros::NodeHandle nh; 

      ros::Subscriber sub = nh.subscribe("core_out", 10, coreCallback);

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

      gettimeofday(&start,NULL); 
      ros::Rate loop_rate(10); 
      while(ros::ok()) 
      { 
            // std::cout << "duration: " << clock() << std::endl;
            struct timeval  end;
            gettimeofday(&end,NULL); 
            auto duration = end.tv_sec - start.tv_sec;
            // std::cout << "duration: " << duration << std::endl;
            if (duration > 7) {
                  robot.idleActInit();
                  gettimeofday(&start,NULL);                   
                  ROS_INFO("Eyes reveive no Msg for 8s: idleAct.");
            }

            ros::spinOnce(); 
            loop_rate.sleep(); 
      } 

      return 0;
}

void init_Action(std::vector<std::pair<int,int>> & target_vec, unsigned int tv_msec)
{

}

