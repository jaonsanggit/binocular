/*
 * robot.h
 * 机器眼结构对象
 * 日期: 2019.10.05
 * 作者: sanghongrui
 */

#ifndef _ROBOT_H
#define _ROBOT_H

#include <ros/ros.h> 
#include <serial/serial.h>  //ROS已经内置了的串口包
#include <serialport/SCServo.h> 

class ROBOTEYES
{
public:
  ROBOTEYES();
  
  void Turn(int w, int h);
  void TurnLR(const std::vector<int> &s);
  void TurnUD(const std::vector<int> &s);
  void TurnShake(const std::vector<int> &s);

  ~ROBOTEYES();
  
private:
    enum DIRATION { Right, Left, UP, Down}; // right, up -> if offset > 0;
    enum {IMAGECenter_W = 480, IMAGECenter_H = 540};
    enum {SERVO_SPEED = 300, SERVO_TIME = 100};
  
  serial::Serial ser;  // declare serial obj
  SCSCL sc;   //  declare SCS  servo obj
  SMSCL sm;   //  declare SMCL servo obj

  void openSerial(const std::string & port, uint32_t  baudrate, uint32_t timeout=1000);
  void eyes_init(const std::map<u8, std::pair<std::string, uint32_t>> & m);
  void spinServo(u8 id, int pos);
  void TurnAction(void);
  void tranform(int h, int w, std::vector<int> & s);
};

#endif