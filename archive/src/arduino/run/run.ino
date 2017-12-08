#include <Servo.h>

#define NEUTRAL 1600

Servo motor;
Servo steering;

void setup() 
{
  //init uart interface
  Serial.begin(9600);

  //open port 9 for the motor, 10 for the steering
  motor.attach(9, 1000, 2000);
  steering.attach(10);
  motor.write(NEUTRAL);
  delay(4000);  
}

int first_time = 0;
void loop() 
{ 
  while(1)
  {
    if(Serial.available()>0)
    {
      char spd = 0, angl = 0;
      Serial.readBytes(&spd, 1);
      Serial.readBytes(&angl, 1);
      motor.write((spd*10)+1000);
      steering.write(angl);

      //Serial.write(spd);
      //Serial.write(angl);
    }
  }
  return;
}
