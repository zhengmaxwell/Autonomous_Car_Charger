#include <Stepper.h>

const int stepPin = 3;
const int dirPin = 2;

int direction = 1; // Up
boolean moving = true; // Moving

char readVal;

int speed = 1000;


Stepper stepper(100, dirPin, stepPin);

void setup()
{
  stepper.setSpeed(speed);
  Serial.begin(9600);
  Serial.println("Start - Moving Up");
}

void loop()
{
  if (Serial.available())
  {
    readVal = Serial.read();
    if (readVal == 'F')
    {
      direction *= -1; // toggle
  
      if (direction == -1)
      {
        Serial.println("DOWN");
      }
      else
      {
        Serial.println("UP");
      }
    }
    
    if (readVal == 'S') // STOP
    {
      moving = false;
      stepper.setSpeed(0);
      Serial.println("STOPPED");
      }
    
    if (readVal == 'G') // GO
    {
      moving = true;
      stepper.setSpeed(speed);
      Serial.println("MOVING");
    }
  }

  if (moving)
  {
    stepper.step(direction);
  }
}