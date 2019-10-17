/*
 * robot.cpp
 * 机器眼结构对象
 * 日期: 2019.10.07
 * 作者: sanghongrui
 */


#include<time.h>
#include <cmath>
#include <serialport/robot.h>
#include <queue>

//const std::map<int, pair<std::string,> servo_init_vec = {590, 675, 670, 785, 336};
const std::map<u8, std::pair<std::string, uint32_t>> servo_init_vec = {
      {1, {"SCS", 590}},
      {2, {"SCS", 675}},
      {3, {"SCS", 670}},
      {4, {"SCS", 785}},
      {5, {"SCS", 500}},
      {6, {"SMCL", 2030}},
      {7, {"SMCL", 2075}}     //2075 3150
};
const std::string port("/dev/ttyUSB0");
const uint32_t baudrate = 115200;

ROBOTEYES::ROBOTEYES() 
{
  openSerial(port, baudrate);
  sc.pSerial = &ser;
  sm.pSerial = &ser;
  
  ROS_INFO("Eyes Init...");
  eyes_init(servo_init_vec);
  ROS_INFO("Eyes Init complte.");
}

ROBOTEYES::~ROBOTEYES()
{
  eyes_init(servo_init_vec);
  ROS_INFO("Eyes Shut Down...");

  ser.close();
}


void ROBOTEYES::idleActInit(void)
{
  eyes_init(servo_init_vec);
}

void ROBOTEYES::Turn(int w, int h, u16 speed)
{
  // clock_t start, stop; //clock_t为clock()函数返回的变量类型
  // start=clock();

  std::vector<int> servoPos(8,0);
  tranform(w, h, servoPos);

  TurnLR(servoPos, speed);
  TurnUD(servoPos, speed);
//  TurnShake(servoPos);
// for (auto v : servoPos)
//     std::cout <<  v << '\t';
// std::cout << '\n';

  TurnAction();
  
  // stop=clock();

  // ROS_INFO("time duration: %ld",stop - start);
}

void ROBOTEYES::TurnLR(const std::vector<int> &s, u16 speed )
{
  spinServo(1, s[1], speed);
  spinServo(3, s[3], speed);
  spinServo(5, s[5], speed);
}

void ROBOTEYES::TurnUD(const std::vector<int> &s, u16 speed)
{
  spinServo(2, s[2], speed);
  spinServo(4, s[4], speed);
  spinServo(7, s[7], speed);
}

void ROBOTEYES::TurnShake(const std::vector<int> &s, u16 speed)
{
  spinServo(6, s[6], speed);
}

void ROBOTEYES::openSerial(const std::string & port, uint32_t  baudrate, uint32_t timeout)
{

  try 
  { 
  //设置串口属性，并打开串口 
    ser.setPort(port); 
    ser.setBaudrate(baudrate); 
    serial::Timeout to = serial::Timeout::simpleTimeout(timeout);
    ser.setTimeout(to); 
    ser.open(); 
  } 
  catch (serial::IOException& e) 
  { 
    ROS_ERROR_STREAM("Unable to open port "); 
  } 
  //检测串口是否已经打开，并给出提示信息 
  if(ser.isOpen()) 
  { 
    ROS_INFO_STREAM("Serial Port initialized"); 
  } 
  else 
  { 
    ROS_ERROR_STREAM("Unable to open port "); 
  }

}

void ROBOTEYES::eyes_init(const std::map<u8, std::pair<std::string, uint32_t>> &m)
{
      for (auto c : m)
            if (c.second.first == "SCS")
                  sc.RegWritePos(c.first,c.second.second, SERVO_TIME, SERVO_SPEED);//舵机(ID),运行至 位置 ,运行时间 , 速度 .
            else 
                  sm.RegWritePos(c.first, c.second.second, SERVO_TIME, SERVO_SPEED);
      sc.RegWriteAction(); 
      sm.RegWriteAction();     
}

void ROBOTEYES::spinServo(u8 id, int pos, u16 speed)
{

  if (servo_init_vec.at(id).first =="SCS")
  {
    sc.RegWritePos(id, pos, SERVO_TIME, speed);
  }else
  {
    sm.RegWritePos(id, pos, SERVO_TIME, speed);
  }

}

void ROBOTEYES::TurnAction(void)
{
  sc.RegWriteAction(); 
  sm.RegWriteAction();
}



void ROBOTEYES::tranform(int w, int h, std::vector<int> & s)
{
  int delta_max_1_3 = 120;  // <= 160
  int delta_max_5 = 80;     // <= 75

  float ratio = 1.5f;
  // if (std::abs(w - IMAGECenter_W) < 200)
  //   ratio = 1.5f;

  s[1] = int(delta_max_1_3*w/IMAGECenter_W*ratio) + servo_init_vec.at(1).second-delta_max_1_3;
  s[3] = int(delta_max_1_3*w/IMAGECenter_W*ratio) + servo_init_vec.at(3).second-delta_max_1_3;
  // s[5] = int(delta_max_5*w/IMAGECenter_W) + servo_init_vec.at(5).second-delta_max_5;
  s[5] = servo_init_vec.at(5).second;

  int delta_max_2_4 = 50;       // d:105 U:170
  int delta_max_7 = 0;  // to do
  s[2] = int(-delta_max_2_4*h/IMAGECenter_H) + servo_init_vec.at(2).second+delta_max_2_4;
  s[4] = int(delta_max_2_4*h/IMAGECenter_H) + servo_init_vec.at(4).second-delta_max_2_4;
  s[7] = servo_init_vec.at(7).second;

  s[6] = servo_init_vec.at(6).second;
}

void ROBOTEYES::Filter(int &w, int &h)
{
  
}