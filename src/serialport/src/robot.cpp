/*
 * robot.cpp
 * 机器眼结构对象
 * 日期: 2019.10.07
 * 作者: sanghongrui
 */


#include <serialport/robot.h>

//const std::map<int, pair<std::string,> servo_init_vec = {590, 675, 670, 785, 336};
const std::map<u8, std::pair<std::string, uint32_t>> servo_init_vec = {
      {1, {"SCS", 590}},
      {2, {"SCS", 675}},
      {3, {"SCS", 670}},
      {4, {"SCS", 785}},
      {5, {"SCS", 500}},
      {6, {"SMCL", 2030}},
      {7, {"SMCL", 3150}}     //2075
};
const std::string port("/dev/ttyUSB0");
const uint32_t baudrate = 115200;

ROBOTEYES::ROBOTEYES() 
{
  openSerial(port, baudrate);
  sc.pSerial = &ser;
  sm.pSerial = &ser;
  eyes_init(servo_init_vec);
}

ROBOTEYES::~ROBOTEYES()
{
  eyes_init(servo_init_vec);
  ser.close();
}


void ROBOTEYES::Turn(int w, int h)
{
  std::vector<int> servoPos(7,0);
  tranform(w, h, servoPos);

  TurnLR(servoPos);
  TurnUD(servoPos);
//  TurnShake(servoPos);
for (auto v : servoPos)
    std::cout <<  v << '\t';
std::cout << '\n';

  TurnAction();
}

void ROBOTEYES::TurnLR(const std::vector<int> &s)
{
  spinServo(1, s[1]);
  spinServo(3, s[3]);
  spinServo(5, s[5]);
}

void ROBOTEYES::TurnUD(const std::vector<int> &s)
{
  spinServo(2, s[2]);
  spinServo(4, s[4]);
  spinServo(7, s[7]);
}

void ROBOTEYES::TurnShake(const std::vector<int> &s)
{
  spinServo(6, s[6]);
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
      ROS_INFO("Eyes Init...");

      for (auto c : m)
            if (c.second.first == "SCS")
                  sc.RegWritePos(c.first,c.second.second, SERVO_TIME, SERVO_SPEED);//舵机(ID),运行至 位置 ,运行时间 , 速度 .
            else 
                  sm.RegWritePos(c.first, c.second.second, SERVO_TIME, SERVO_SPEED);
      sc.RegWriteAction(); 
      sm.RegWriteAction();
      
      ROS_INFO("Eyes Init complte.");
}

void ROBOTEYES::spinServo(u8 id, int pos)
{

  if (servo_init_vec.at(id).first =="SCS")
  {
    sc.RegWritePos(id, pos, SERVO_TIME, SERVO_SPEED);
  }else
  {
    sm.RegWritePos(id, pos, SERVO_TIME, SERVO_SPEED);
  }

}

void ROBOTEYES::TurnAction(void)
{
  sc.RegWriteAction(); 
  sm.RegWriteAction();
}

void ROBOTEYES::tranform(int w, int h, std::vector<int> & s)
{
  int delta_max_1_3 = 60;
  int delta_max_5 = 40;
  s[1] = int(delta_max_1_3*w/IMAGECenter_W) + servo_init_vec.at(1).second-delta_max_1_3;
  s[3] = int(delta_max_1_3*w/IMAGECenter_W) + servo_init_vec.at(3).second-delta_max_1_3;
  s[5] = int(delta_max_5*w/IMAGECenter_W) + servo_init_vec.at(5).second-delta_max_5;

  int delta_max_2_4 = 50;
  int delta_max_7 = 0;  // to do
  s[2] = int(-delta_max_2_4*h/IMAGECenter_H) + servo_init_vec.at(2).second+delta_max_2_4;
  s[4] = int(delta_max_2_4*h/IMAGECenter_H) + servo_init_vec.at(4).second-delta_max_2_4;
  s[7] = servo_init_vec.at(7).second;

  s[6] = servo_init_vec.at(6).second;
}