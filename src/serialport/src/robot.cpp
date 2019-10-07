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
  ser.close();
}


void ROBOTEYES::Turn(const std::pair<int, int> & faceLocation)
{
  int delta_w = faceLocation.first - IMAGECenter_W;
  int delta_h = faceLocation.second - IMAGECenter_H;

  tranform(delta_w, delta_h);

  TurnEyes(delta_w, delta_h);
}

void ROBOTEYES::TurnEyes(const int delta_w, const int delata_h)
{
  spinServo(1, delta_w);
  spinServo(3, delta_w);
  spinServo(2, delata_h);
  spinServo(4, delata_h);
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

void ROBOTEYES::spinServo(u8 id, int offset)
{

  if (servo_init_vec.at(id).first =="SCS")
  {
    int currentPos = sc.ReadPos(id);
    sc.RegWritePos(id, currentPos+offset, SERVO_TIME, SERVO_SPEED);
  }else
  {
    int currentPos = sm.ReadPos(id);
    sm.RegWritePos(id, currentPos+offset, SERVO_TIME, SERVO_SPEED);
  }

}

void ROBOTEYES::spinServoAction(void)
{
  sc.RegWriteAction(); 
  sm.RegWriteAction();
}

void ROBOTEYES::tranform(int &w, int &h)
{
  w = w * 330 / 480;
  h = h * 295 / 540;
}