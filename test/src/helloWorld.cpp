#include <ros/ros.h>
#include <std_msgs/String.h>

/****************

  / -> start , global parameter

  ~ -> start , private parameter

    -> start , relative parameter

  **************/

int main(int argc, char **argv)
{
  ros::init(argc, argv, "helloWorld");

  ros::NodeHandle nh("~");	// will make Parameter be /helloWorld/... , if not global

  std::string s;
  
  nh.setParam("ggggg/my_test", "TEST");	// create /helloeWorld/ggggg/my_test & set value in node

  if (nh.getParam("my_param", s))	// get /helloWorld/my_param value , if it has been created
  {
	  ROS_INFO("Got param: %s", s.c_str());
  }
  else
  {
	  ROS_ERROR("Failed to get param 'my_param'");
  }

  
  ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("chatter", 1000);  // publish topic /helloWorld/chatter , if arg1 is "/chatter" then topic is /chatter

  ros::Rate loop_rate(10);

  while(ros::ok()){

  	std_msgs::String msg;
	msg.data = "HELLOWORLD";

	chatter_pub.publish(msg);

	ros::spinOnce();
  }
}
