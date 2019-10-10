/*
 * SCServo.cpp
 * 飞特串行舵机硬件接口层程序
 * 日期: 2017.8.22
 * 作者: 谭雄乐
 */


#include "serialport/SCSerail.h"
#include "time.h"
#include <string>
using std::string;

SCSerail::SCSerail()
{
	IOTimeOut = 100;
	pSerial = NULL;
}

SCSerail::SCSerail(u8 End):SCS(End)
{
	IOTimeOut = 100;
	pSerial = NULL;
}

SCSerail::SCSerail(u8 End, u8 Level):SCS(End, Level)
{
	IOTimeOut = 100;
	pSerial = NULL;
}

int SCSerail::readSCS(unsigned char *nDat, int nLen)
{
	int Size = 0;
	string ComData;
	clock_t t_begin, t_user;
	while(1){
		ComData = pSerial->read();
		if(ComData.length() == 1){
			if(nDat){
				nDat[Size] = ComData[0];
			}
			Size++;
			t_begin = clock();
		}
		if(Size>=nLen){
			break;
		}
		t_user = clock() - t_begin;
		if(t_user>IOTimeOut){
			break;
		}
	}
	return Size;
}

int SCSerail::writeSCS(unsigned char *nDat, int nLen)
{
	if(nDat==NULL){
		return 0;
	}
 return pSerial->write(nDat, nLen);
}

int SCSerail::writeSCS(unsigned char bDat)
{
	return pSerial->write(&bDat, 1);
}

void SCSerail::flushSCS()
{
	// while(pSerial->read() != -1);
	pSerial->flushInput();
}