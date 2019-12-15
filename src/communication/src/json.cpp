
#include "json.h"
#include <string>

using namespace std;

/**** msgFromiFlytek Json format *****
*	{
*	  "name":"甘坤",
*	  "emotion":"puzzled",
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
void MsgFromiFlytek::extract_Json(const char* key, char* json, char* dest){

	char* start = NULL;
	char* end   = NULL;

	/*extract dest from Json*/
	if(strstr(json, key)!=NULL){
		start = strstr(json, key);
		start += strlen(key);  

		for(end = start; *end != '\"' && *end!='\0'; ++end);
    	memcpy(dest, start, end-start);
    	dest[end-start] = 0;
	}
}


/**** msgToiFlytek Json format *******
*	{
*	  "command":"idle",
*	  "name":"甘坤",
*	  "gender":"male",
*	  "age":"23",
*	}
**************************************/
void MsgToiFlytek::generate_Json(string cmd, string name, string gender, uint16_t age, char* destinaton){

    string json;

    json = "{\"command\":\"" + cmd + "\",\"name\":\"" + name + "\",\"gender\":\"" + gender + "\",\"age\":\"" + to_string(age) + "\"}"; 

    strcpy(destinaton,json.c_str());

}


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
void MsgTofronEnd::generate_Json(string pageStatus, string name, string gender, uint16_t age, string speechRecoResult, string DrinkName, string CupNum, string CupType, string Temp, string orderFinish, char* destinaton){

    string json;

	//CupNum
	if(CupNum=="一杯")
		json = "{\"pageStatus\":\"" + pageStatus + "\",\"name\":\"" + name + "\",\"gender\":\"" + gender + "\",\"age\":\"" + to_string(age) + "\",\"speechRecoResult\":\"" + speechRecoResult + "\",\"OrderInfo\":{\"DrinkName\":\"" + DrinkName + "\",\"CupNum\":\"1\",\"CupType\":\"";
	else if(CupNum=="两杯")
		json = "{\"pageStatus\":\"" + pageStatus + "\",\"name\":\"" + name + "\",\"gender\":\"" + gender + "\",\"age\":\"" + to_string(age) + "\",\"speechRecoResult\":\"" + speechRecoResult + "\",\"OrderInfo\":{\"DrinkName\":\"" + DrinkName + "\",\"CupNum\":\"2\",\"CupType\":\"";
	else if(CupNum=="三杯")
		json = "{\"pageStatus\":\"" + pageStatus + "\",\"name\":\"" + name + "\",\"gender\":\"" + gender + "\",\"age\":\"" + to_string(age) + "\",\"speechRecoResult\":\"" + speechRecoResult + "\",\"OrderInfo\":{\"DrinkName\":\"" + DrinkName + "\",\"CupNum\":\"3\",\"CupType\":\"";
	else if(CupNum=="四杯")
		json = "{\"pageStatus\":\"" + pageStatus + "\",\"name\":\"" + name + "\",\"gender\":\"" + gender + "\",\"age\":\"" + to_string(age) + "\",\"speechRecoResult\":\"" + speechRecoResult + "\",\"OrderInfo\":{\"DrinkName\":\"" + DrinkName + "\",\"CupNum\":\"4\",\"CupType\":\"";
	else
		json = "{\"pageStatus\":\"" + pageStatus + "\",\"name\":\"" + name + "\",\"gender\":\"" + gender + "\",\"age\":\"" + to_string(age) + "\",\"speechRecoResult\":\"" + speechRecoResult + "\",\"OrderInfo\":{\"DrinkName\":\"" + DrinkName + "\",\"CupNum\":\"\",\"CupType\":\"";
	
	
    
	//CupType
	if(CupType=="小杯")
		json += "0\",\"Temp\":\""; 
	else if(CupType=="大杯")
		json += "1\",\"Temp\":\""; 
	else
		json += "\",\"Temp\":\""; 
	
	//Temp
	if(Temp=="冰的")
		json += "0\",\"orderFinish\":\"" + (orderFinish) + "\"}}"; 
	else if(Temp=="热的")
		json += "1\",\"orderFinish\":\"" + (orderFinish) + "\"}}"; 
	else
		json += "\",\"orderFinish\":\"" + (orderFinish) + "\"}}"; 
	

    strcpy(destinaton,json.c_str());

}