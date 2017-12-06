#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>
#include <ros/ros.h>
#include <serial_node/Serial.h>
#include <iostream>
#include <nav_msgs/Odometry.h>

float x;

void path(const nav_msgs::Odometry::ConstPtr& odom)
{
x = odom->pose.pose.position.x;
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "Serial_node");
  ros::NodeHandle n;
  ros::Publisher sender = n.advertise<serial_node::Serial>("/serial/actuator", 100);
  ros::Subscriber receiver = n.subscribe("/zed/odom", 100, path);
  ros::Rate loop_rate(1);

  int rpm = 1700;
  int angle = 90;
  int cnt = 0;
  while(ros::ok() && x<0.20 && cnt<20)
  {
       
    serial_node::Serial msg;
    msg.speed_rpm = rpm;
    msg.angle_degrees = angle;
    sender.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
    cnt ++;
  }

    serial_node::Serial msg;
    msg.speed_rpm = 1600;
    msg.angle_degrees = 60;
    sender.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();

  return 0;
}

