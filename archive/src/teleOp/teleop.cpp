#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>
#include <pthread.h>

using namespace std;

//file locations
#define STEERING "steering.txt"
#define THROTTLE "throttle.txt"

//steps for throttle and steering
#define TTL_STEP 2
#define STR_STEP 1

//buffer for saving the last few thousand keys pressed
int CUR_CMD = 0;
#define NUMBER_COMMANDS 10000
const char* SAVED_COMMANDS[NUMBER_COMMANDS];
//write a float (as an int) to a generic file
void writeFile(float val, const char* file)
{
 //open the file
 FILE* fp = fopen(file, "w");
 //print an int to the file
 fprintf(fp, "%d", (int)val);
 //close the file
 fclose(fp);
}

//read the keyboard input to the terminal, and return the result as an integer (decimal ASCII value)
int getKey()
{
 int c;
 struct termios old_settings;
 struct termios new_settings;

 //get the normal terminal settings
 tcgetattr(fileno(stdin), &old_settings);
 //copy all the old settings to the new settings
 memcpy(&new_settings, &old_settings, sizeof(struct termios));
 //make the settings so calls to stdin are automatically captured
 new_settings.c_lflag &= ~(ECHO | ICANON);
 new_settings.c_cc[VTIME] = 0;
 new_settings.c_cc[VMIN] = 0;
 //apply the new settings
 tcsetattr(fileno(stdin), TCSANOW, &new_settings);
 //read the input
 c = fgetc(stdin);
 //reapply the old settings to resume normal terminal operations
 tcsetattr(fileno(stdin), TCSANOW, &old_settings);

 return c;
}

//convert the keyboard input into human-readable form (also useful for checking which specific key was pressed
const char* getASCII()
{
 int rawkey = getKey();
 //arrow keys have 3 getkey calls, 2 to signify an arrow key was pressed, and the 3rd to distinguish which was pressed
 if(rawkey == 27)
 {
  rawkey = getKey();
  if(rawkey == 27 || rawkey == -1)
  {
   return "ESC";
  }
  else if(rawkey == 91)
  {
   rawkey = getKey();
   //3 ternary operators on one line (condition) ? run_if_true : run_if_false
   return (rawkey == 65 ? "UP" : rawkey == 66 ? "DOWN" : rawkey == 67 ? "RIGHT" : "LEFT");
  }
 }

 //upper case letters
 else if(65 <= rawkey && rawkey <= 90)
 {
  char *buffer = (char*)malloc(sizeof(char)*2);
  sprintf(buffer, "%c", ('A' + (rawkey - 65)));
  return buffer;
 }
 //lowercase letters
 else if(97 <= rawkey && rawkey <= 122)
 {
    char *buffer = (char*)malloc(sizeof(char)*2);
  sprintf(buffer, "%c", ('a' + (rawkey - 97)));
  return buffer;
 }
 //0-9
 else if(48 <= rawkey && rawkey <= 57)
 {
  char *buffer = (char*)malloc(sizeof(char)*2);
  sprintf(buffer, "%c", ('0' + (rawkey - 48)));
  return buffer;
 }
 //enter key
 else if(rawkey == 10)
 {
  return "ENTER";
 }
 //tab
 else if(rawkey == 9)
 {
  return "TAB";
 }
 //spacebar
 else if(rawkey == 32)
 {
  return "SPACE";
 }
 //delete (mac)
 else if(rawkey == 126)
 {
  return "DEL";
 }
 //backspace (mac)
 else if(rawkey == 127)
 {
  return "BACKSPACE";
 }
 //rawkey == -1, no key read
 return NULL;
}

//make a vehicle class
class Vehicle
{
public:
 //public variables
 float throttle, steering;

 //assignment constructor
 Vehicle(float t=1600.0f, float s=90.0f): throttle(t), steering(s) {}
 //print to standard output
 friend ostream& operator <<(ostream& output, const Vehicle& car)
 {
  output << "Throttle = " << (int)car.throttle <<
	 " , Steering = " << (int)car.steering;
  return output;
 }

 //functions adapted directly from python
 void throttle_forward()
 {
  this->throttle += TTL_STEP;
  writeFile(this->throttle, THROTTLE);
 }
 void throttle_reverse()
 {
  this->throttle -= TTL_STEP;
  writeFile(this->throttle, THROTTLE);
 }
 void steer_right()
 {
  this->steering += STR_STEP;
  writeFile(this->steering, STEERING);
 }
 void steer_left()
 {
  this->steering -= STR_STEP;
  writeFile(this->steering, STEERING);
 }
 void hard_right()
 {
  this->steering = 125;
  writeFile(this->steering, STEERING);
 }
 void hard_left()
 {
  this->steering = 65;
  writeFile(this->steering, STEERING);
 }
 void hard_brake()
 {
  if(1900 > this->throttle && this->throttle > 1650)
  {
   this->throttle = 1050;
   writeFile(this->throttle, THROTTLE);
   usleep(10);
   goToPark();
  } else if(1100 < this->throttle && this->throttle < 1550) {
   this->throttle = 1950;
   writeFile(this->throttle, THROTTLE);
   usleep(10);
   goToPark();
  }
 }
 void goToPark()
 {
  this->throttle = 1600;
  this->steering = 90;
  writeFile(1600, THROTTLE);
  writeFile(90, STEERING);
 }
};

//print the teleop message, taken from the python code
void showDash(const Vehicle& car)
{
 const char *header="\
               ****************************************************************************\n\
               ******                    **Networked Systems Lab**                   ******\n\
               ******                     TeleOp V.1.0.1 Running                     ******\n\
               ******                                                                ******\n\
               ******                              |W|                               ******\n\
               ******                                                                ******\n\
               ******       Hard Left: |Q|    |A|  |S|  |D|    Hard Right: |E|       ******\n\
               ******                                                                ******\n\
               ******                         |B|       |P|                          ******\n\
               ******                        Brake      Park                         ******\n\
               ****************************************************************************\n\
               Odometry Info:\n\
               ";
 const char *second_header = "               ****************************************************************************\n\
               Press \"0\" to Terminate\n\
\
               TeleOp by: Behrad Toghi, NSL\n\
               C++ version: Christian Theriot\n\
               ****************************************************************************\n";
/*               Throttle = %lf , Steering = %lf\*/
 //clear the screen
 system("clear");
 std::cout << flush;

 //print the message
 std::cout << header << flush;
 std::cout << car << std::endl << flush;
 std::cout << second_header << std::endl << flush;
}

//check if the ascii version of the current key matches some desired value
bool isKey(const char* left, const char* right)
{
 return left != NULL && right != NULL && (strcmp(left, right) == 0 ? true : false);
}

//check if the key is in the buffer
bool checkCommands(const char* cmd)
{
 for(int i = 0; i < NUMBER_COMMANDS; i++)
 {
  if(isKey(cmd, SAVED_COMMANDS[i])) return true;
 }
 return false;
}
//add the key to the buffer
void addCommand(const char* cmd)
{
 SAVED_COMMANDS[CUR_CMD] = cmd;
 CUR_CMD++;
 CUR_CMD %= NUMBER_COMMANDS;
}

int main(int argc, char** argv)
{
 //make an instance of the car class
 Vehicle car;
 //state variables
 bool brake = false, steer = false, validated = false;
 int down_time = 0;

 //pseudo-infinite loop
 while(1)
 {
  //get the command (NULL if no keyboard input or between key presses)
  const char* key = getASCII();
  addCommand(key);
  if(key == NULL)
  {
   //don't print every cycle!
   if(!validated)
   {
    showDash(car);
    validated = true;
   }
  } else {
   //time to reprint
   down_time = 0;
   validated = false;
  }

  if(isKey(key, "w") || isKey(key, "W"))
  {
   car.throttle_forward();
  }
  if(isKey(key, "a") || isKey(key, "A"))
  {
   car.steer_left();
  }
  if(isKey(key, "s") || isKey(key, "S"))
  {
   car.throttle_reverse();
  }
  if(isKey(key, "d") || isKey(key, "D"))
  {
   car.steer_right();
  }

  if(steer && key == NULL && down_time > 128 && !checkCommands("q") && !checkCommands("Q") && !checkCommands("e") && !checkCommands("E"))
  {
   car.steering = 90;
   writeFile(90, STEERING);
   steer = false;
   validated = false;
  }
  if(isKey(key, "e") || isKey(key, "E"))
  {
   car.hard_right();
   steer = true;
  }
  if(isKey(key, "q") || isKey(key, "Q"))
  {
   car.hard_left();
   steer = true;
  }

  if(brake && key == NULL && down_time > 128 && !checkCommands("w") && !checkCommands("W") && !checkCommands("S") && !checkCommands("s"))
  {
   car.throttle = 1600;
   writeFile(1600, THROTTLE);
   brake = false;
   validated = false;
  }
  if(isKey(key, "b") || isKey(key, "B"))
  {
   car.hard_brake();
   brake = true;
  }
  if(isKey(key, "p") || isKey(key, "P"))
  {
   car.goToPark();
  }
  if(isKey(key, "0"))
  {
   car.goToPark();
   std::cout << "\n **Program Terminated**\n";
   break;
  }

  down_time++;
 }

 return 0;
}
