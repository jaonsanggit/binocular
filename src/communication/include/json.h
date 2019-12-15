#ifndef _JSON_H
#define _JSON_H

#include <iostream>
#include <string.h>
#include <stdint.h>
#include <limits.h>

using namespace std;

/**** msgFromiFlytek Json format *****
*	{
*	  "name":"甘坤",
*	  "emotion":"puzzled",
*     "greetingDone":"false",
*	  "speechRecoResult":"null",
*	  "OrderInfo":
*	   {
*	 	 "DrinkName":"null",
*	 	 "CupNum":"null",
*	 	 "CupType":"null",
*	 	 "Temp":"null",
*	 	 "OrderFinish":"0"
*	   } 
*	}
**************************************/
class MsgFromiFlytek
{

public:
	const char* keyName        = "\"name\":\"";
	const char* keyEmotion     = "\"emotion\":\"";
	const char* keyGreetingDone     = "\"greetingDone\":\"";
	const char* keySpeechRecoResult = "\"speechRecoResult\":\"";
	const char* keyDrinkName        = "\"DrinkName\":\"";
	const char* keyCupNum 			= "\"CupNum\":\"";
	const char* keyCupType 			= "\"CupType\":\"";
	const char* keyTemp			    = "\"Temp\":\"";
	const char* keyOrderFinish = "\"OrderFinish\":\"";

public:

	char name[24]        = "";
	char emotion[24]     = "";
	char greetingDone[10]      = "";
	char speechRecoResult[512] = "";
	char DrinkName[30]         = "";
	char CupNum[20]             = "";
	char CupType[20]            = "";
	char Temp[20]               = "";
	char OrderFinish[10]       = "";

	char Json[PIPE_BUF+1];

	void extract_Json(const char* key, char* json, char* dest);
};



/**** msgToiFlytek Json format *****
*	{
*	  "command":"idle",
*	  "name":"甘坤",
*	  "gender":"male",
*	  "age":"23",
*	}
**************************************/
class MsgToiFlytek
{
public:

	string cmd      = "idle";
	string name     = "unknown";
	uint16_t age    = 0;
	string gender   = "unknown";
	char Json[PIPE_BUF+1];

	void generate_Json(string cmd, string name, string gender, uint16_t age, char* destinaton);

};


/**** msgTofrontEnd Json format *****
*	{
*	  "pageStatus":"orderInfo",
*	  "name":"甘坤",
*	  "gender":"male",
*	  "age":"23",
*	  "speechRecoResult":"null",
*	  "OrderInfo":
*	   {
*	 	 "DrinkName":"拿铁"",
*	 	 "CupNum":"1",
*	 	 "CupType":"0",     //0->小杯  1->大杯
*	 	 "Temp":"0",        //0->冰的  1->热的
*	 	 "OrderFinish":"true"
*	   } 
*	}
**************************************/
class MsgTofronEnd
{
public:

	string pageStatus = "idle"; // ROS中做逻辑判断
	string name     = "unknown";
	uint16_t age    = 0;
	string gender   = "unknown";

	string speechRecoResult = "";
	string DrinkName        = "";
	string CupNum           = "";
	string CupType          = "";
	string Temp             = "";
	string OrderFinish      = "";

	char Json[PIPE_BUF+1];

	void generate_Json(string pageStatus, string name, string gender, uint16_t age, string speechRecoResult, string DrinkName, string CupNum, string CupType, string Temp, string orderFinish, char* destinaton);
	
};

#endif