#include <ros/ros.h> 
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <serial/serial.h>  //ROS已经内置了的串口包 
#include <std_msgs/String.h> 
#include <std_msgs/Empty.h> 
#include <serialport/SCServo.h>
#include "serialport/CJsonObject.hpp"

serial::Serial ser; //声明串口对象
SCSCL sc;   //  declara servor obj
SMSCL sm;
void eyes_init(const std::map<u8, std::pair<std::string, u16>> & m);

//const std::map<int, pair<std::string,> servo_init_vec = {590, 675, 670, 785, 336};
const std::map<int, std::pair<std::string, int>> servo_init_vec = {
      {1, {"SCS", 590}},
      {2, {"SCS", 675}},
      {3, {"SCS", 670}},
      {4, {"SCS", 785}},
      {5, {"SCS", 336}},
      {6, {"SMCL", 1500}},
      {7, {"SMCL", 3140}}     //2100
};

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

      try 
      { 
      //设置串口属性，并打开串口 
            ser.setPort("/dev/ttyUSB0"); 
            ser.setBaudrate(115200); 
            //ser.setBaudrate(1000000); 
            serial::Timeout to = serial::Timeout::simpleTimeout(1000); 
            ser.setTimeout(to); 
            ser.open(); 
      } 
      catch (serial::IOException& e) 
      { 
            ROS_ERROR_STREAM("Unable to open port "); 
            return -1; 
      } 
      //检测串口是否已经打开，并给出提示信息 
      if(ser.isOpen()) 
      { 
            ROS_INFO_STREAM("Serial Port initialized"); 
      } 
      else 
      { 
            return -1; 
      } 

      sc.pSerial = &ser;
      sm.pSerial = &ser;

      //eyes_init(servo_init_vec);
      //指定循环的频率 
      ros::Rate loop_rate(1); 
      while(ros::ok()) 
      { 
        //ROS_INFO("Write name.\n\n");
        //sc.WritePos(2, 580, 2000);//舵机(ID1),运行至1023位置,运行时间T=2000ms

        size_t n = ser.available();
        if(n!=0)
        {
            uint8_t buffer[1024];
            //读出数据
            n = ser.read(buffer, n);
            
            for(int i=0; i<n; i++)
            {
                //16进制的方式打印到屏幕
                 std::cout << std::hex << (buffer[i] & 0xff) << " ";
            }
             std::cout << std::endl;
        }

      //处理ROS的信息，比如订阅消息,并调用回调函数 
            ros::spinOnce(); 
            loop_rate.sleep(); 
      } 
      ser.close();
      return 0;
} 

void eyes_init(const std::map<int, std::pair<std::string, int>> &m)
{
      ROS_INFO("Servo Init...");

      for (auto c : m)
            if (c.second.first == "SCS")
                  sc.RegWritePos(c.first,c.second.second, 100, 100);//舵机(ID),运行至 位置 ,运行时间 , 速度 .
            else 
                  sm.RegWritePos(c.first, c.second.second, 100, 100);
      sc.RegWriteAction(); 
      sm.RegWriteAction();
      
      ROS_INFO("Servo Init complte.");
}