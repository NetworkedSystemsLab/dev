#include <ros.h>
#include <std_msgs/Int32.h>
#include <iostream>

int main(int argc, char** argv)
{
  ros::init(argc, argv, "serial");
  ros::NodeHandle n;
  ros::Publisher sender = n.advertise<std_msgs::Int32>("/serial/arduino", 10);
  ros::Rate loop_rate(10);

  while(ros::ok())
  {
	std_msgs::Int32 rpm, angle;
	std::cin >> rpm.data;
	sender.publish(rpm);
	ros::spinOnce();
	std::cin >> angle;
	sender.publish(angle);
	ros::spinOnce();
	loop_rate.sleep();
  }
  return 0;
}
