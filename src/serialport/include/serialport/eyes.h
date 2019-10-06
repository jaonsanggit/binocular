/*
 * eyes.h
 * 机器眼结构对象
 * 日期: 2019.10.05
 * 作者: sanghongrui
 */

#ifndef _EYES_H
#define _EYES_H

#include <ros/ros.h> 
#include <serial/serial.h>  //ROS已经内置了的串口包
#include <serialport/SCServo.h> 

class ROBOTEYES
{
public:
  ROBOTEYES();
  
  void Turn(int offset); //int - > u16
  void TurnEyes(int offset);
  void TurnNecks(int offset); 
  
private:
    enum DIRATION { Right, Left, UP, Down}; // right, up -> if offset > 0;
  int servo_speed; // servo spin speed
  //int servo_time; 
  serial::Serial serial;  // declare serial obj
  SCSCL sc;   //  declare SCS  servo obj
  SMSCL sm;   //  declare SMCL servo obj

  void openSerial(const std::string serialport, uint32_t  baudrate, uint32_t timeout=1000);
  void eyes_init(const std::map<u8, std::pair<std::string, u8>> & m);
  void spinServo(u8 id, u16 offset, DIRATION dir);
};

#endif