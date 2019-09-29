#include <ros/ros.h> 
#include <std_msgs/String.h> 
#include <std_msgs/Empty.h> 

void eyesCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("core heard [%s] from eyes.", msg->data.c_str());
}

int main(int argc, char **argv) {

  ros::init(argc, argv, "core");

  ros::NodeHandle n;

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("core", 1000);

  ros::Subscriber sub = n.subscribe("eyes", 1000, eyesCallback);

  ros::Rate loop_rate(1);

  /**
   * A count of how many messages we have sent. This is used to create
   * a unique string for each message.
   */
  int count = 0;
  while (ros::ok())
  {
    /**
     * This is a message object. You stuff it with data, and then publish it.
     */
    std_msgs::String msg;

    std::stringstream ss;
    ss << "ONService" << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    /**
     * The publish() function is how you send messages. The parameter
     * is the message object. The type of this object must agree with the type
     * given as a template parameter to the advertise<>() call, as was done
     * in the constructor above.
     */
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}