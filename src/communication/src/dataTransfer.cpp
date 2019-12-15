
/**
 * ROS Node: Data Transfer Centre, Connecting the Core & iFlytek.
 */
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sstream>
#include <iostream>
#include <string.h>
#include "ros/ros.h"
#include "std_msgs/String.h"

#include "../include/json.h"
#include "../../../devel/include/msgfile/VoiceOrder.h"
#include "../../../devel/include/msgfile/Core2Voice.h"


#define SELF_TEST

// #define TO_FRONT_END
// 模拟数据转发给DSS
// #define FRONT_END_SIMULATION


using namespace ros;
using namespace std;

MsgFromiFlytek msgFromiFlytek;
MsgToiFlytek msgToiFLytek;
MsgTofronEnd msgTofrontEnd;

/** file description of named pipe */
int pipe_fd_wr_iFlytek = -1;
int pipe_fd_rd_iFlytek = -1;
int pipe_fd_wr_frontEnd = -1;


/** 该回调函数用于接收来自Core的Msg，并转发至iFlytek */
void chatterCallback(const msgfile::Core2Voice::ConstPtr& msg){  

	/** message to iFlytek */
	/** cmd暂时手动控制 */
	msgToiFLytek.cmd    = msg->cmd;
	msgToiFLytek.name   = msg->name;
	msgToiFLytek.gender = msg->gender;
	msgToiFLytek.age    = msg->age;
	/** message to frontEnd */
	msgTofrontEnd.name   = msg->name;
	msgTofrontEnd.gender = msg->gender;
	msgTofrontEnd.age    = msg->age;

	msgToiFLytek.generate_Json(msgToiFLytek.cmd, msgToiFLytek.name, msgToiFLytek.gender, msgToiFLytek.age, msgToiFLytek.Json);

	cout << "============================================================================================" << endl;
	cout << "[ CHATTER_CALLBACK ] " << msgToiFLytek.Json << endl << endl;

	/** write()当FIFO写满时才阻塞，否则不阻塞并且返回错误！ */
	int res = write(pipe_fd_wr_iFlytek, msgToiFLytek.Json, strlen(msgToiFLytek.Json));
	// if(res == -1) 
		;// fprintf(stderr, "Write error on pipe\n");
}



/** thread used to write to front end */
/*==== msgTofrontEnd Json format =======================/
/	{													/					
/	  "pageStatus":"orderInfo",							/	
/	  "name":"kevin",								 	/
/	  "gender":"male",									/						
/	  "age":"23",										/
/	  "speechRecoResult":"null",						/
/	  "OrderInfo":										/
/	   {												/
/	 	 "DrinkName":"latte"",							/						
/	 	 "CupNum":"1",									/
/	 	 "CupType":"0",     //0->小杯  1->大杯			 
/	 	 "Temp":"0",        //0->冰的  1->热的
/	 	 "OrderFinish":"true"							/
/	   } 												/
/	}													/
/======================================================*/
#ifdef TO_FRONT_END
void* _writeTofrontEnd(void* arg){

	/** Create FIFO: RD_ONLY & BLOCKING */
	// const char *fifo_name = "../../../intelligentvoiceordering/myfifo/ros_2_frontEnd";
	const char *fifo_name = "/home/aibar/intelligentvoiceordering/myfifo/ros_2_frontEnd";
	int res = 0;
	int open_mode; 

#ifdef FRONT_END_SIMULATION
	open_mode = O_WRONLY;  //O_NONBLOCK 
#else
	open_mode = O_WRONLY;
#endif

	if(access(fifo_name, F_OK) == -1){
		res = mkfifo(fifo_name, 0777);
		if(res != 0){
			fprintf(stderr, "Could not create fifo %s\n", fifo_name);
			exit(EXIT_FAILURE);
		}
	}
	pipe_fd_wr_frontEnd = open(fifo_name, open_mode);

	if(pipe_fd_wr_frontEnd == -1)    
		cout << "[ WRITE_TO_FRONT_END ] open err " << endl;
	else 
		cout << "[ WRITE_TO_FRONT_END ] open successfully!" << endl;
	


#ifdef FRONT_END_SIMULATION
	/*==================================================================================
	=                                 SIMULATION                                       =
	==================================================================================*/
	msgTofrontEnd.pageStatus = "idle"; 
	msgTofrontEnd.name       = "甘坤";
	msgTofrontEnd.gender     = "male";
	msgTofrontEnd.age        = 18;

	msgTofrontEnd.DrinkName   = "卡布奇诺";
	msgTofrontEnd.CupNum      = "三杯";
	msgTofrontEnd.Temp        = "热的";
	msgTofrontEnd.CupType     = "大杯";
	// msgTofrontEnd.OrderFinish = "true";

	while (1){
		
		/** 无服务对象，处于空闲状态 */
		/** idle:欢迎页面,只需要指定pageStatus即可，其余信息均为空 */
		msgTofrontEnd.generate_Json("idle", "unknown", "unknown", 00, "", "", "", "", "", "", msgTofrontEnd.Json);
		int res = write(pipe_fd_wr_frontEnd, msgTofrontEnd.Json, strlen(msgTofrontEnd.Json));
		cout << "============================================================================================" << endl;
		cout << "[ WRITE_TO_FRONT_END ] " << msgTofrontEnd.Json << endl << endl;
		usleep(1000*5000);
		
		/** 服务对象出现，页面状态切换为working，大眼睛语音问候开始,界面显示全部饮品菜单以及推荐饮品 */
		/** working：需发送顾客身份信息以及语音识别内容 */
		msgTofrontEnd.generate_Json("working", msgTofrontEnd.name, msgTofrontEnd.gender, msgTofrontEnd.age, "我要一杯卡布奇诺", msgTofrontEnd.DrinkName, "", "", "", "false", msgTofrontEnd.Json);
		res = write(pipe_fd_wr_frontEnd, msgTofrontEnd.Json, strlen(msgTofrontEnd.Json));
		cout << "============================================================================================" << endl;
		cout << "[ WRITE_TO_FRONT_END ] " << msgTofrontEnd.Json << endl << endl;
		usleep(1000*4000);
		
		msgTofrontEnd.generate_Json("working", msgTofrontEnd.name, msgTofrontEnd.gender, msgTofrontEnd.age, "冰的", "", "", "", "", "false", msgTofrontEnd.Json);
		res = write(pipe_fd_wr_frontEnd, msgTofrontEnd.Json, strlen(msgTofrontEnd.Json));
		cout << "============================================================================================" << endl;
		cout << "[ WRITE_TO_FRONT_END ] " << msgTofrontEnd.Json << endl << endl;
		usleep(1000*4000);
		
		msgTofrontEnd.generate_Json("working", msgTofrontEnd.name, msgTofrontEnd.gender, msgTofrontEnd.age, "还是换成热的吧", "", "", "", "", "false", msgTofrontEnd.Json);
		res = write(pipe_fd_wr_frontEnd, msgTofrontEnd.Json, strlen(msgTofrontEnd.Json));
		cout << "============================================================================================" << endl;
		cout << "[ WRITE_TO_FRONT_END ] " << msgTofrontEnd.Json << endl << endl;
		usleep(1000*4000);
		
		msgTofrontEnd.generate_Json("working", msgTofrontEnd.name, msgTofrontEnd.gender, msgTofrontEnd.age, "是的", "", "", "", "", "false", msgTofrontEnd.Json);
		res = write(pipe_fd_wr_frontEnd, msgTofrontEnd.Json, strlen(msgTofrontEnd.Json));
		cout << "============================================================================================" << endl;
		cout << "[ WRITE_TO_FRONT_END ] " << msgTofrontEnd.Json << endl << endl;
		usleep(1000*2000);

		/** 顾客确认订单信息后，则显示订单详情 */
		/** orerInfo:发送顾客身份信息，以及订单信息 */
		msgTofrontEnd.DrinkName   = "卡布奇诺";
		msgTofrontEnd.generate_Json("orderInfo", msgTofrontEnd.name, msgTofrontEnd.gender, msgTofrontEnd.age, "", msgTofrontEnd.DrinkName, msgTofrontEnd.CupNum, msgTofrontEnd.CupType, msgTofrontEnd.Temp, "false", msgTofrontEnd.Json);
		res = write(pipe_fd_wr_frontEnd, msgTofrontEnd.Json, strlen(msgTofrontEnd.Json));
		cout << "[ WRITE_TO_FRONT_END ] " << msgTofrontEnd.Json << endl << endl;
		usleep(1000*100);
		msgTofrontEnd.generate_Json("orderInfo", msgTofrontEnd.name, msgTofrontEnd.gender, msgTofrontEnd.age, "", msgTofrontEnd.DrinkName, msgTofrontEnd.CupNum, msgTofrontEnd.CupType, msgTofrontEnd.Temp, "true", msgTofrontEnd.Json);
		res = write(pipe_fd_wr_frontEnd, msgTofrontEnd.Json, strlen(msgTofrontEnd.Json));
		cout << "[ WRITE_TO_FRONT_END ] " << msgTofrontEnd.Json << endl << endl;
		usleep(1000*5000);
	}
#else

	/*==================================================================================
	=                             STATE  MACHINE                                       =
	==================================================================================*/
	while(1){
		bool isChange = false;
		string pageStatus_temp 	= "idle"; // ROS中做逻辑判断
		string name_temp      	= "unknown";
		string gender_temp 	 	= "unknown";
		uint16_t age_temp    	= 0;

		string speechRecoResult_temp = "";
		string DrinkName_temp        = "";
		string CupNum_temp           = "";
		string CupType_temp          = "";
		string Temp_temp             = "";
		string OrderFinish_temp      = "";

		if(pageStatus_temp != msgTofrontEnd.pageStatus ||
		   name_temp != msgTofrontEnd.name ||
		   gender_temp != msgTofrontEnd.gender ||
		   age_temp != msgTofrontEnd.age ||
		   speechRecoResult_temp != msgTofrontEnd.speechRecoResult ||
		   DrinkName_temp != msgTofrontEnd.DrinkName ||
		   CupNum_temp != msgTofrontEnd.CupNum ||
		   CupType_temp != msgTofrontEnd.CupType ||
		   Temp_temp != msgTofrontEnd.Temp ||
		   OrderFinish_temp != msgTofrontEnd.OrderFinish
		){
			isChange = true;
		}

		/** State Transition */ 
		/** "idle"->"workking"->"orderInfo" */
		if(msgToiFLytek.cmd!="working"){
			msgTofrontEnd.pageStatus = "idle";
		}
		else if(msgTofrontEnd.pageStatus=="idle" && msgToiFLytek.cmd=="working"){
			msgTofrontEnd.pageStatus = "working";	
		}
		else if(msgTofrontEnd.pageStatus=="working" && strcmp(msgFromiFlytek.OrderFinish,"true")==0){
			msgTofrontEnd.pageStatus = "orderInfo";
		}

		//something changes!
		if(isChange){
			isChange = false;
			pageStatus_temp = msgTofrontEnd.pageStatus;
			name_temp = msgTofrontEnd.name;
			gender_temp = msgTofrontEnd.gender;
			age_temp = msgTofrontEnd.age;
			speechRecoResult_temp = msgTofrontEnd.speechRecoResult;
			DrinkName_temp = msgTofrontEnd.DrinkName;
			CupNum_temp = msgTofrontEnd.CupNum;
			CupType_temp = msgTofrontEnd.CupType;
			Temp_temp = msgTofrontEnd.Temp;
			OrderFinish_temp = msgTofrontEnd.OrderFinish;

			/** 无服务对象，处于空闲状态,显示欢迎页面 */
			/** idle:只需要指定pageStatus即可，其余信息为空 */
			if(msgTofrontEnd.pageStatus=="idle"){
				msgTofrontEnd.generate_Json("idle", "unknown", "unknown", 00, "", "", "", "", "", "", msgTofrontEnd.Json);
				int res = write(pipe_fd_wr_frontEnd, msgTofrontEnd.Json, strlen(msgTofrontEnd.Json));
				cout << "============================================================================================" << endl;
				cout << "[ WRITE_TO_FRONT_END ] " << msgTofrontEnd.Json << endl << endl;
			}

			/** 服务对象出现，页面状态切换为working，大眼睛语音问候开始,界面显示全部饮品菜单以及推荐饮品 */
			/** working：需发送顾客身份信息以及语音识别内容 */
			else if(msgTofrontEnd.pageStatus=="working"){
				msgTofrontEnd.generate_Json("working", msgTofrontEnd.name, msgTofrontEnd.gender, msgTofrontEnd.age, msgFromiFlytek.speechRecoResult, msgTofrontEnd.DrinkName, msgTofrontEnd.CupNum, msgTofrontEnd.CupType, msgTofrontEnd.Temp, "fasle", msgTofrontEnd.Json);
				res = write(pipe_fd_wr_frontEnd, msgTofrontEnd.Json, strlen(msgTofrontEnd.Json));
				cout << "============================================================================================" << endl;
				cout << "[ WRITE_TO_FRONT_END ] " << msgTofrontEnd.Json << endl << endl;
			}

			/** 顾客确认订单信息后，则界面显示订单详情 */
			/** orerInfo:发送顾客身份信息，以及订单信息 */
			else if(msgTofrontEnd.pageStatus=="orderInfo"){
				//默认大杯，后续增添询问环节	
				msgTofrontEnd.CupType = "大杯";
				msgTofrontEnd.generate_Json("orderInfo", msgTofrontEnd.name, msgTofrontEnd.gender, msgTofrontEnd.age, "", msgTofrontEnd.DrinkName, msgTofrontEnd.CupNum, msgTofrontEnd.CupType, msgTofrontEnd.Temp, "false", msgTofrontEnd.Json);
				res = write(pipe_fd_wr_frontEnd, msgTofrontEnd.Json, strlen(msgTofrontEnd.Json));
				cout << "============================================================================================" << endl;
				cout << "[ WRITE_TO_FRONT_END ] " << msgTofrontEnd.Json << endl << endl;
				usleep(1000*50);
				msgTofrontEnd.CupType = "大杯";
				msgTofrontEnd.generate_Json("orderInfo", msgTofrontEnd.name, msgTofrontEnd.gender, msgTofrontEnd.age, "", msgTofrontEnd.DrinkName, msgTofrontEnd.CupNum, msgTofrontEnd.CupType, msgTofrontEnd.Temp, "true", msgTofrontEnd.Json);
				res = write(pipe_fd_wr_frontEnd, msgTofrontEnd.Json, strlen(msgTofrontEnd.Json));
				cout << "============================================================================================" << endl;
				cout << "[ WRITE_TO_FRONT_END ] " << msgTofrontEnd.Json << endl << endl;
			}
		}
		// usleep(1000*100);
	}
#endif
}
#endif




/** thread used to write FIFO to iFlytek  */
/*==== msgToiFlytek Json format ===========/
/	{								       /
/	  "command":"idle",				       /
/	  "name":"kevin",				       / 				
/	  "gender":"male",				       /
/	  "age":"23",					       /
/	}								       /
/=========================================*/
void* _writeToiFLytek(void* arg){

	/** Create FIFO: RD_ONLY & BLOCKING */
	const char *fifo_name = "/home/aibar/intelligentvoiceordering/myfifo/ros_2_iFlytek";
	// const char *fifo_name = "~/intelligentvoiceordering/myfifo/ros_2_iFlytek";
	int res = 0;
	const int open_mode = O_WRONLY; //| O_NONBLOCK ;  

	if(access(fifo_name, F_OK) == -1){
		res = mkfifo(fifo_name, 0777);
		if(res != 0){
			fprintf(stderr, "Could not create fifo %s\n", fifo_name);
			exit(EXIT_FAILURE);
		}
	}
	pipe_fd_wr_iFlytek = open(fifo_name, open_mode);

	if(pipe_fd_wr_iFlytek == -1)    
		cout << "[ WRITE_TO_IFLYTEK ] open err " << endl;
	else 
		cout << "[ WRITE_TO_IFLYTEK ] open successfully!" << endl;

#ifdef SELF_TEST

	string cmd    = "idle";
	string name   = "甘坤";
	string gender = "male";
	uint16_t age  = 23;
	msgToiFLytek.cmd    = cmd;
	msgToiFLytek.name   = name;
	msgToiFLytek.gender = gender;
	msgToiFLytek.age    = age;

	while(1){
		// cout << "[ '_writeToiFLytek' ] Input command: ";
		cin >> msgToiFLytek.cmd;
		msgToiFLytek.generate_Json(msgToiFLytek.cmd, msgToiFLytek.name, msgToiFLytek.gender, msgToiFLytek.age, msgToiFLytek.Json);
		write(pipe_fd_wr_iFlytek, msgToiFLytek.Json, strlen(msgToiFLytek.Json));
	}

#endif

}


/** thread used to read FIFO & publish topic-> VoicePub */
/*==== msgFromiFlytek Json format ==========================/
/	{														/	
/	  "name":"kevin",										/	
/	  "emotion":"puzzled",									/	
/     "greetingDone":"false",								/	
/	  "speechRecoResult":"null",							/	
/	  "OrderInfo":											/	
/	   {													/
/	 	 "DrinkName":"null",								/	
/	 	 "CupNum":"null",									/	
/	 	 "CupType":"null",									/	
/	 	 "Temp":"null",										/	
/	 	 "OrderFinish":"0"									/	
/	   } 													/
/	}														/
/==========================================================*/
void* _readFromiFLytek(void* arg){

	ros::NodeHandle n;

	/** publish数据,消息格式VoiceOrder.msg */
	ros::Publisher chatter_pub = n.advertise<msgfile::VoiceOrder>("VoicePub", 1000);

	/** msg transfered to Core */
	msgfile::VoiceOrder msg2core;

	const char *fifo_name = "/home/aibar/intelligentvoiceordering/myfifo/iFlytek_2_ros";
	// const char *fifo_name = "../../../../intelligentvoiceordering/myfifo/iFlytek_2_ros";
	int open_mode = O_RDONLY;
	char buffer[PIPE_BUF+1];
	int bytes_read = 0; 

	/** Empty the buffer */
	memset(buffer, '\0', sizeof(buffer));
 
	/** RD_ONLY & BLOCKING */
	pipe_fd_rd_iFlytek = open(fifo_name, open_mode);

	if(pipe_fd_rd_iFlytek == -1)  
		cout << "[ READ_FROM_IFLYTEK ] open err !" << endl;
	else
		cout << "[ READ_FROM_IFLYTEK ] open successfully !" << endl;

	while(1){

		/** read operation blocked, wait until iFLytek:write_end */
		bytes_read = read(pipe_fd_rd_iFlytek, buffer, PIPE_BUF);

		if(bytes_read==-1){

			cout << "[ READ_FROM_IFLYTEK ] read err!!!" << endl;
			close(pipe_fd_rd_iFlytek);

			pipe_fd_rd_iFlytek = open(fifo_name, open_mode);
			if(pipe_fd_rd_iFlytek == -1)   cout << "[ READ_FROM_IFLYTEK ] open err!!! " << endl;
		}
		else if(bytes_read>0){

			buffer[bytes_read] = 0;
			strcpy(msgFromiFlytek.Json,buffer); 
		}
		else
			;

		cout << "============================================================================================" << endl;
		cout << "[ READ_FROM_IFLYTEK ] " << msgFromiFlytek.Json << endl << endl;

		/** 解析iFlytek的数据 */
		msgFromiFlytek.extract_Json(msgFromiFlytek.keyName, msgFromiFlytek.Json, msgFromiFlytek.name);
		msgFromiFlytek.extract_Json(msgFromiFlytek.keyEmotion, msgFromiFlytek.Json, msgFromiFlytek.emotion);
		msgFromiFlytek.extract_Json(msgFromiFlytek.keySpeechRecoResult, msgFromiFlytek.Json, msgFromiFlytek.speechRecoResult);
		msgFromiFlytek.extract_Json(msgFromiFlytek.keyGreetingDone, msgFromiFlytek.Json, msgFromiFlytek.greetingDone);
		msgFromiFlytek.extract_Json(msgFromiFlytek.keyDrinkName, msgFromiFlytek.Json, msgFromiFlytek.DrinkName);
		msgFromiFlytek.extract_Json(msgFromiFlytek.keyCupNum, msgFromiFlytek.Json, msgFromiFlytek.CupNum);
		msgFromiFlytek.extract_Json(msgFromiFlytek.keyCupType, msgFromiFlytek.Json, msgFromiFlytek.CupType);
		msgFromiFlytek.extract_Json(msgFromiFlytek.keyTemp, msgFromiFlytek.Json, msgFromiFlytek.Temp);
		msgFromiFlytek.extract_Json(msgFromiFlytek.keyOrderFinish, msgFromiFlytek.Json, msgFromiFlytek.OrderFinish);
		
		/** 订单信息转发至前端 */
		msgTofrontEnd.DrinkName   = msgFromiFlytek.DrinkName;
		msgTofrontEnd.CupNum      = msgFromiFlytek.CupNum;
		msgTofrontEnd.CupType     = msgFromiFlytek.CupType;
		msgTofrontEnd.Temp        = msgFromiFlytek.Temp;
		msgTofrontEnd.OrderFinish = msgFromiFlytek.OrderFinish;

		/** 转发至Core的数据 */
		msg2core.name = msgFromiFlytek.name;
		msg2core.emotion = msgFromiFlytek.emotion;
		msg2core.OrderFinish = strcmp(msgFromiFlytek.OrderFinish,"true")==0 ? true : false;
		
		chatter_pub.publish(msg2core);
	}
}



int main(int argc, char** argv){

	ros::init(argc, argv, "dataTransfer");

	ros::NodeHandle n;

	/** Subscribe Jason topic:'core_voice',Core2Voice.msg */
	ros::Subscriber chatter_sub = n.subscribe("core_voice", 1000, chatterCallback);

	ros::Rate loop_rate(100);
	
	/** write FIFO thread */
	pthread_t writeToiFLytek;
	/** read FIFO thread */
	pthread_t readFromiFLytek;
	/** write FIFO thread */
	pthread_t writeTofrontEnd;

	int ret = pthread_create(&writeToiFLytek, NULL, _writeToiFLytek, NULL);
	if (ret != 0) {
		printf("order pthread_create error: error_code = %d\n", ret);
	}

	ret = pthread_create(&readFromiFLytek, NULL, _readFromiFLytek, NULL);
	if (ret != 0){ 
		printf("getCmd pthread_create error: error_code = %d\n", ret);
	}
#ifdef TO_FRONT_END
	ret = pthread_create(&readFromiFLytek, NULL, _writeTofrontEnd, NULL);
	if (ret != 0){
		printf("getCmd pthread_create error: error_code = %d\n", ret);
	}
#endif

	while(1){

		msgfile::VoiceOrder test_msg;

		// chatter_pub.publish(test_msg);

		/** 10ms，睡眠时间尽量短，spinOnce()函数调用频率高 */
		loop_rate.sleep();

		/** 调用此函数时才会去执行回调函数，消息发送频率高于spinOnce调用频率时，注意消息池大小的合理设置！ */
		ros::spin();

	}

	return 0;

}