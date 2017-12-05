#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <time.h>

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

int main(void)
{
  int fd = open_port();
  configure_port(fd);

  int forward = 1800, neutral = 1600;


  char transmitted_byte = (char)((forward - 1000)/10);
  write(fd, &transmitted_byte, 1);

  char c;
  scanf("%c", &c);

  transmitted_byte = (char)((neutral - 1000)/10);
  write(fd, &transmitted_byte, 1);

  close(fd);
  return 0;
}

