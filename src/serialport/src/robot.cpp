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
  int w1 = 0, w3 = 0;
  int h2 = 0, h4 = 0;
  tranform(w, h, w1, w3, h2, h4);

  TurnEyes(w1, w3, h2, h4);
}

void ROBOTEYES::TurnEyes(int w1, int w3 , int h2, int h4)
{
  spinServo(1, w1);
  spinServo(3, w3);
  spinServo(2, h2);
  spinServo(4, h4);
  spinServoAction();
}

void ROBOTEYES::TurnNecks(int w, int h)
{

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
                  sc.RegWritePos(c.first,c.second.second, 100, 100);//舵机(ID),运行至 位置 ,运行时间 , 速度 .
            else 
                  sm.RegWritePos(c.first, c.second.second, 100, 100);
      sc.RegWriteAction(); 
      sm.RegWriteAction();
      
      ROS_INFO("Eyes Init complte.");
}

void ROBOTEYES::spinServo(u8 id, int pos)
{

  if (servo_init_vec.at(id).first =="SCS")
  {
    std::cout << int(id) << ": " << pos << std::endl;
    sc.RegWritePos(id, pos, SERVO_TIME, SERVO_SPEED);
  }else
  {
    std::cout << int(id) << ": " << pos << std::endl;
    sm.RegWritePos(id, pos, SERVO_TIME, SERVO_SPEED);
  }

}

void ROBOTEYES::spinServoAction(void)
{
  sc.RegWriteAction(); 
  sm.RegWriteAction();
}

void ROBOTEYES::tranform(int w, int h, int & w1, int & w3 , int & h2, int & h4)
{
  w1 = int(0.36f*w) + 419;
  w3 = int(0.31f*w) + 520;
  h2 = int(-0.00015f*h*h - 0.13f*h) + 787;
  h4 = int(0.000114883f*h*h + 0.13241f*h) + 680;
}