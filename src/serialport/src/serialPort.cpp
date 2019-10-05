#include <ros/ros.h> 
#include <serial/serial.h>  //ROS已经内置了的串口包 
#include <std_msgs/String.h> 
#include <std_msgs/Empty.h> 
#include <serialport/SCServo.h>

serial::Serial ser; //声明串口对象
SCSCL sc;   //  declara servor obj
void eyes_init(const std::vector<int> & vec);

const std::vector<int> servo_init_vec = {590, 675, 670, 785, 336};

int main (int argc, char** argv) 
{ 
      //初始化节点 
      ros::init(argc, argv, "serialport"); 
      //声明节点句柄 
      ros::NodeHandle nh; 

      try 
      { 
      //设置串口属性，并打开串口 
            ser.setPort("/dev/ttyUSB0"); 
            ser.setBaudrate(115200); 
            //ser.setBaudrate(1000000); 
            serial::Timeout to = serial::Timeout::simpleTimeout(1000); 
            ser.setTimeout(to); 
            ser.open(); 
      } 
      catch (serial::IOException& e) 
      { 
            ROS_ERROR_STREAM("Unable to open port "); 
            return -1; 
      } 
      //检测串口是否已经打开，并给出提示信息 
      if(ser.isOpen()) 
      { 
            ROS_INFO_STREAM("Serial Port initialized"); 
      } 
      else 
      { 
            return -1; 
      } 

      sc.pSerial = &ser;

      eyes_init(servo_init_vec);
      //指定循环的频率 
      ros::Rate loop_rate(1); 
      while(ros::ok()) 
      { 
        //ROS_INFO("Write name.\n\n");
        //sc.WritePos(2, 580, 2000);//舵机(ID1),运行至1023位置,运行时间T=2000ms

        size_t n = ser.available();
        if(n!=0)
        {
            uint8_t buffer[1024];
            //读出数据
            n = ser.read(buffer, n);
            
            for(int i=0; i<n; i++)
            {
                //16进制的方式打印到屏幕
                 std::cout << std::hex << (buffer[i] & 0xff) << " ";
            }
             std::cout << std::endl;
        }

      //处理ROS的信息，比如订阅消息,并调用回调函数 
            ros::spinOnce(); 
            loop_rate.sleep(); 
      } 
      ser.close();
      return 0;
} 

void eyes_init(const std::vector<int> & vec)
{
      ROS_INFO("Servo Init...");

      int i = 0;
      for (auto v : vec)
            sc.RegWritePos(++i,v, 100, 100);//舵机(ID),运行至 位置 ,运行时间 , 速度 .
      sc.RegWriteAction(); 

      ROS_INFO("Servo Init complte.");
}