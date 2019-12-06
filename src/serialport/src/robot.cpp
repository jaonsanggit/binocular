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
      {1, {"SCS", 521}},
      {2, {"SCS", 439}},
      {3, {"SCS", 486}},
      {4, {"SCS", 520}},
      {5, {"SCS", 800}},
      {6, {"SMCL", 772}},
      {7, {"SMCL", 2980}}     //2075
};

const std::map<u8, std::pair<std::string, uint32_t>> servo_idle_vec = {
      {1, {"SCS", 521}},
      {2, {"SCS", 617}},
      {3, {"SCS", 486}},
      {4, {"SCS", 357}},
      {5, {"SCS", 800}},
      {6, {"SMCL", 772}},
      {7, {"SMCL", 2980}}     //2075
};

const std::string port("/dev/ttyUSB0");
const uint32_t baudrate = 115200;

ROBOTEYES::ROBOTEYES() 
{
  openSerial(port, baudrate);
  sc.pSerial = &ser;
  sm.pSerial = &ser;
  
  ROS_INFO("Eyes Init...");
  idleActInit();
  ROS_INFO("Eyes Init complte.");
}

ROBOTEYES::~ROBOTEYES()
{
  idleActInit();
  ROS_INFO("Eyes Shut Down...");

  ser.close();
}


void ROBOTEYES::idleActInit(void)
{
  eyes_init(servo_idle_vec);
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

void ROBOTEYES::TurnBend(int pos, u16 speed)
{
  spinServo(7, pos, speed);
  TurnAction();
}

void ROBOTEYES::openSerial(const std::string & port, uint32_t  baudrate, uint32_t timeout)
{

  try 
  { 
  //设置串口属性，并打开串口 0
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
  int delta_max_1_3 = 140;  // <= 160
  // int delta_max_5 = 80;     // <= 75

  float ratio = 1.5f;
  // if (std::abs(w - IMAGECenter_W) < 200)
  //   ratio = 1.5f;

  // s[1] = int(-delta_max_1_3*w) + servo_init_vec.at(1).second-delta_max_1_3;
  // s[3] = int(-delta_max_1_3*w) + servo_init_vec.at(3).second-delta_max_1_3;
  // s[5] = int(delta_max_5*w/IMAGECenter_W) + servo_init_vec.at(5).second-delta_max_5;

  s[1] = -delta_max_1_3*w/50 + servo_init_vec.at(1).second+delta_max_1_3;
  s[3] = -delta_max_1_3*w/50 + servo_init_vec.at(3).second+delta_max_1_3;
  s[5] = servo_init_vec.at(5).second;

  int delta_max_2_4 = 150;       // d:105 U:170
  // int delta_max_7 = 0;  // to do

  // s[2] = int(delta_max_2_4*h) + servo_init_vec.at(2).second+delta_max_2_4;
  // s[4] = int(delta_max_2_4*h) + servo_init_vec.at(4).second-delta_max_2_4;
  s[2] = delta_max_2_4*h/50 + servo_init_vec.at(2).second-delta_max_2_4;
  s[4] = -delta_max_2_4*h/50 + servo_init_vec.at(4).second+delta_max_2_4;
  s[7] = servo_init_vec.at(7).second;

  s[6] = servo_init_vec.at(6).second;
}

void ROBOTEYES::Filter(int &w, int &h)
{
  
}

// void ROBOTEYES::emtionAction(std::string emotion)
// {
//   std::vector<int> init = {0,590,675,670,785,500,2030,3150};

//   if (emotion == "confused"){
//     std::vector<int> vec = {0, 573, 769, 682, 705, 473, init[6], init[7]}; 
    
//     struct timeval  start = {0, 0}, end = {0, 0};
//     gettimeofday(&start,NULL); 

//     TurnLR(vec, 200);
//     TurnUD(vec, 200);
//     TurnAction();
//   }


 