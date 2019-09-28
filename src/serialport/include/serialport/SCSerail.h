/*
 * SCServo.h
 * ���ش��ж��Ӳ���ӿڲ����
 * ����: 2017.8.22
 * ����: ̷����
 */

#ifndef _SCSERIAL_H
#define _SCSERIAL_H

// #if defined(ARDUINO) && ARDUINO >= 100
// #include "Arduino.h"
// #else
// #include "WProgram.h"
// #endif

#include "serialport/SCS.h"
#include <serial/serial.h>  //ROS�Ѿ������˵Ĵ��ڰ� 

class SCSerail : public SCS
{
public:
	SCSerail();
	SCSerail(u8 End);
	SCSerail(u8 End, u8 Level);
	virtual int writeSCS(unsigned char *nDat, int nLen);//���nLen�ֽ�
	virtual int readSCS(unsigned char *nDat, int nLen);//����nLen�ֽ�
	virtual int writeSCS(unsigned char bDat);//���1�ֽ�
	virtual void flushSCS();//ˢ�½ӿڻ�����
public:
	unsigned long int IOTimeOut;//���������ʱ
	serial::Serial *pSerial;//����ָ��
};

#endif