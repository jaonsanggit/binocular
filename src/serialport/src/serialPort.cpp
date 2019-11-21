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
static u16 target_s = 400;

static struct timeval start = {0, 0};
static std::string pre_cmd = "idle";


// init->working 会有鞠躬动作
void coreCallback(const msgfile::FaceTarget::ConstPtr& msg)
{
      gettimeofday(&start,NULL); 

      if (msg->cmd == "idle") {
            ROS_INFO("\n--------------IDLE------------------"); 
            ROS_INFO("  Receive idle status."); 
            robot.idleActInit();
            ROS_INFO("  Eyes idleAct.");
            pre_cmd = "idle";
            return ;
      }

      else if (msg->header.frame_id != "core") {
            ROS_INFO("\n-------------NOT CORE-------------------");             
            ROS_INFO("  Receive msg but not from core."); 
            return ;            
      }

      else if (msg->cmd == "init") {
            ROS_INFO("\n------------INIT--------------------");
            pre_cmd = "init";
      }

      else {
            // std::vector<uint8_t> name = msg->user_name;
            ROS_INFO("\n--------------WORKING------------------"); 
            if(pre_cmd == "init"){
                  robot.TurnBend(1950, 200);                  
                  struct timeval bend = {0, 0};
                  struct timeval bendover = {0, 0};
                  gettimeofday(&bend, NULL);
                  gettimeofday(&bendover, NULL);
                  while ((bendover.tv_sec - bend.tv_sec)*1000.0f + (bendover.tv_usec - bend.tv_usec)/1000.0f < 500.0f){
                        std::cout << "bending" << std::endl;
                        gettimeofday(&bendover, NULL);
                  }
                  robot.TurnBend(2075, 200);
                  pre_cmd = "working";
                  return;
            }
      }

      target_w = int(msg->target.x);
      target_h = int(msg->target.y);
      target_s = u16(msg->target.z);
      std::cout << "  frame_id:" << msg->header.frame_id << std::endl;
      // setlocale(LC_CTYPE, "zh_CN.utf8");
      // std::cout << "  user_name: " << msg->name << std::endl;
      std::cout << "  target_w: " << target_w << '\t' 
                << "  target_h: " << target_h << '\t' 
                << "  target_s: " << target_s
                << std::endl << std::endl; 

      robot.Turn(target_w, target_h, target_s);
}


// 没有鞠躬动作
void coreCallback1(const msgfile::FaceTarget::ConstPtr& msg)
{
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
            return;            
      }

      else if (msg->cmd == "init") {
            ROS_INFO("\n------------INIT--------------------");
      }

      else {
            ROS_INFO("\n--------------WORKING------------------"); 
      }

      target_w = int(msg->target.x);
      target_h = int(msg->target.y);
      target_s = u16(msg->target.z);
      std::cout << "  frame_id:" << msg->header.frame_id << std::endl;
      // setlocale(LC_CTYPE, "zh_CN.utf8");
      // std::cout << "  user_name: " << msg->name << std::endl;
      std::cout << "  target_w: " << target_w << '\t' 
                << "  target_h: " << target_h << '\t' 
                << "  target_s: " << target_s
                << std::endl << std::endl; 

      robot.Turn(target_w, target_h, target_s);
}


int main (int argc, char** argv) 
{ 
      //初始化节点 
      ros::init(argc, argv, "serialport"); 
      //声明节点句柄 
      ros::NodeHandle nh; 

      ros::Subscriber sub = nh.subscribe("core_eyes", 10, coreCallback1);
      
      gettimeofday(&start,NULL); 
      ros::Rate loop_rate(10); 
      while(ros::ok()) 
      { 
            // std::cout << "duration: " << clock() << std::endl;
            struct timeval  end;
            gettimeofday(&end,NULL); 
            auto duration = end.tv_sec - start.tv_sec;
            // std::cout << "duration: " << duration << std::endl;
            if (duration > 5) {
                  robot.idleActInit();
                  gettimeofday(&start,NULL);                   
                  ROS_INFO("Eyes reveive no Msg for 8s: idleAct.");
            }

            ros::spinOnce(); 
            loop_rate.sleep(); 
      } 

      return 0;
}

