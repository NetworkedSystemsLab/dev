#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <time.h>

#define ERROR_THRESHOLD 1000

#define FULL_REVERSE 1000;
#define NEUTRAL 1500;
#define FULL_THROTTLE 2000;

#define FULL_LEFT 66;
#define PARK_ANGLE 90;
#define FULL_RIGHT 131;

#define THROTTLE_FILE "throttle"
#define STEERING_FILE "steering"
int THROTTLE_ERROR = 0;
int STEERING_ERROR = 0;


//get the serial device
int open_port(void);

//prepare serial for writing
int configure_port(int fd);

int main(void)
{
  int fd = open_port();
  configure_port(fd);

  int previous_steering_angle = PARK_ANGLE;
  int previous_throttle_rpm = NEUTRAL;
  int current_steering_angle = PARK_ANGLE;
  int current_throttle_rpm = NEUTRAL;
  for(1)
  {
    FILE* throttle_file = fopen(THROTTLE_FILE, "r");
    FILE* steering_file = fopen(STEERING_FILE, "r");

    fscanf(throttle_file, "%d", &current_throttle_rpm);
    fscanf(steering_file, "%d", &current_steering_angle);
    if(FULL_REVERSE <= current_throttle_rpm && current_throttle_rpm <= FULL_FORWARD)
    {
      previous_throttle_rpm = current_throttle_rpm;
    } else {
      THROTTLE_ERROR++;
    }
    if(FULL_LEFT <= current_steering_angle && current_steering_angle <= FULL_RIGHT)
    {
      previous_steering_angle = current_throttle_angle;
    } else {
      STEERING_ERROR++;
    }
    if(THROTTLE_ERROR >= ERROR_THRESHOLD || STEERING_ERROR >= ERROR_THRESHOLD)
    {
      fclose(throttle_file);
      fclose(steering_file);break;
    }

    char bytes[2];
    bytes[0] = (previous_throttle_rpm - 1000) / 10;
    bytes[1] = previous_steering_angle;
    for( int b = 0; b < 2; b++ )
    {
      write(fd, &bytes[b], 1);
    }

    fclose(throttle_file);
    fclose(steering_file);
  }

  close(fd);
  return 0;
}

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
