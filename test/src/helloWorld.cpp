#include <ros/ros.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "helloWorld");
  ros::NodeHandle nh;

  std::string s;
  //nh.setParam("my_param", "TEST");
  if (nh.getParam("my_param", s))
  {
	  ROS_INFO("Got param: %s", s.c_str());
  }
  else
  {
	  ROS_ERROR("Failed to get param 'my_param'");
  }

  //ROS_INFO("Hello world!");
}
