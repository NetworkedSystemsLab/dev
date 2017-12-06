#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>
#include <ros/ros.h>
#include <serial_node/Serial.h>
#include <iostream>

#define SERIAL_PORT "/dev/ttyACM0"

int open_port(void)
{
  int location;
  location = open(SERIAL_PORT, O_RDWR | O_NOCTTY | O_NDELAY);
  if(location == -1)
  {
    printf("open_port: Unable to open %s.\n", SERIAL_PORT);
  } else {
    fcntl(location, F_SETFL, 0);
    printf("port is open.\n");
  }

  return location;
}

int configure_port(int port)
{
  struct termios settings;
  cfsetispeed(&settings, B9600);
  cfsetospeed(&settings, B9600);
  settings.c_cflag &= ~PARENB;
  settings.c_cflag &= ~CSTOPB;
  settings.c_cflag &= ~CSIZE;
  settings.c_cflag |= CS8;

  tcsetattr(port, TCSANOW, &settings);
  return port;
}

int _serial = -1;

void serialCallback(const serial_node::Serial::ConstPtr& msg)
{
  std::cout << msg->speed_rpm;
  std::cout << ", ";
  std::cout << msg->angle_degrees;
  std::cout << std::endl;

  char byte = (char)((msg->speed_rpm-1000)/10);
  write(_serial, &byte, 1);
  byte = (char)(int)msg->angle_degrees;
  write(_serial, &byte, 1);
}
int main(int argc, char** argv)
{

  _serial = open_port();
  configure_port(_serial);

  ros::init(argc, argv, "Serial_node");
  ros::NodeHandle n;

  ros::Subscriber receiver = n.subscribe("/serial/actuator", 100, serialCallback);
  ros::spin();
  close(_serial);
  return 0;
}

