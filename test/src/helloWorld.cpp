#include <ros/ros.h>
#include <std_msgs/String.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "helloWorld");
  ros::NodeHandle nh("~");	// will make Parameter be /helloWorld/...

  std::string s;
  
  nh.setParam("my_test", "TEST");	// create /helloeWorld/my_test & set value in node

  if (nh.getParam("my_param", s))	// get /helloWorld/my_param value , if it has been created
  {
	  ROS_INFO("Got param: %s", s.c_str());
  }
  else
  {
	  ROS_ERROR("Failed to get param 'my_param'");
  }

  
  ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("/chatter", 1000);  // publish topic /chatter

  ros::Rate loop_rate(10);

  while(ros::ok()){

  	std_msgs::String msg;
	msg.data = "HELLOWORLD";

	chatter_pub.publish(msg);

	ros::spinOnce();
  }
}
