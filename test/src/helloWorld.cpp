#include <ros/ros.h>

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

  //ROS_INFO("Hello world!");
}
