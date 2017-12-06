#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include "gpio_jetson_library.h"
#include "ultrasonic_library.h"

using namespace std;

#define THRESHOLD 30
#define STRAIGHT 90
#define LEFT 65
#define RIGHT 115


//get the serial device
int open_port(void)
{
  int fd;
  fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY);

  if(fd == -1)
  {
    printf("open_port: Unable to open /dev/ttyACM0.\n");
  } else {
    fcntl(fd, F_SETFL, 0);
    printf("port is open.\n");
  }
  return fd;
}

//prepare serial for writing
int configure_port(int fd)
{
  struct termios port_settings;
  cfsetispeed(&port_settings, B9600);
  cfsetospeed(&port_settings, B9600);

  port_settings.c_cflag &= ~PARENB;
  port_settings.c_cflag &= ~CSTOPB;
  port_settings.c_cflag &= ~CSIZE;
  port_settings.c_cflag |= CS8;

  tcsetattr(fd, TCSANOW, &port_settings);
  return fd;
}

void forward(int fd)
{
  char send = 65, straight = STRAIGHT;
  write(fd, &send, 1);
  cout << send << endl;
  write(fd, &straight, 1);
}
void neutral(int fd)
{
  char send = 60, straight = STRAIGHT;
  write(fd, &send, 1);
  write(fd, &straight, 1);
}
void left(int fd)
{
  char send = 65, left = LEFT;
  write(fd, &send, 1);
  write(fd, &left, 1);
}
void right(int fd)
{
  char send = 65, right = RIGHT;
  write(fd, &send, 1);
  write(fd, &right, 1);
}

int main(void)
{
  HCSR04 *ultrasonic = new HCSR04();
  ultrasonic->exportGPIO();
  ultrasonic->setDirection();


  int fd = open_port();
  configure_port(fd);

  //int forward = 1750, neutral = 1600;

  forward(fd);

  int cnt = 0;

  int direction = 0;
  while(1)
  {
      if(cnt > 20)
      {
        direction++;
      }
//    if(cnt > 200) break;
    unsigned int duration = ultrasonic->pingMedian(5);
    if(duration != NO_ECHO)
    {
      float dist = duration/58.0;
      if(dist < THRESHOLD)
      {
        neutral(fd);
      } else {
 	if(direction % 3 == 0)	
		forward(fd);
	else if(direction % 3 == 1)
 		left(fd);

	else 	right(fd);
      }
    }
    usleep(10000);
    cnt++;
  }
  neutral(fd);
  ultrasonic->unexportGPIO();
  close(fd);
  return 0;
}

