#include <Stepper.h>

/***** Define Pins *****/

int const xDirPin = 2;
int const xStepPin = 3;
int const yDirPin = 4;
int const yStepPin = 5;
int const zDirPin = 6;
int const zStepPin = 7;

/***** Define Stepper Motor Values *****/

int const xSpeed = 200;
int const xSteps = 200;
int const ySpeed = 200;
int const ySteps = 200;
int const zSpeed = 200;
int const zSteps = 200;

Stepper xStepper(xSteps, xDirPin, xStepPin);
Stepper yStepper(ySteps, yDirPin, yStepPin);
Stepper zStepper(zSteps, zDirPin, zStepPin);

/***** Define Starting Movement *****/

int xDirection = 1; // TODO: Check which direction this is
int yDirection = 1; // TODO: Check which direction this is
int zDirection = 1; // UP

boolean xMoving = false; // Still
boolean yMoving = false; // Still
boolean zMoving = false; // Still

char readVal; // Serial Input Variable
char motorVal; // Keeps track of which motor active


void setup()
{
    xStepper.setSpeed(xSpeed);
    yStepper.setSpeed(ySpeed);
    zStepper.setSpeed(zSpeed);

    Serial.begin(9600);
    Serial.println("Start");
}

void loop()
{
    while (Serial.available())
    {
        readVal = Serial.read();

        if (readVal == 'X') // X Motor
        {
            enableX();
        }
        if (readVal == 'Y') // Y Motor
        {
            enableY();
        }
        if (readVal == 'Z') // Z Motor
        {
            enableZ();
        }

        if (readVal == 'F') // Flip Direction
        {
            flip();
        }

        if (readVal == 'S') // Stop
        {
            stop();
        }
        if (readVal == 'G') // Go
        {
            go();
        }
    }

    step();
}


void enableX()
{
    if (yMoving || zMoving)
    {
        stop();
    }
    motorVal = 'X';
    Serial.println("X Motor: RIGHT"); // TODO: Check Direction
}
void enableY()
{
    if (xMoving || zMoving)
    {
        stop();
    }
    motorVal = 'Y';
    Serial.println("Y Motor: FORWARDS"); // TODO: Check Direction
}
void enableZ()
{
    if (xMoving || yMoving)
    {
       stop(); 
    }
    motorVal = 'Z';
    Serial.println("Z Motor: UP");
}

void flip()
{
    if (motorVal == 'X')
    {
        flipX();
    }
    else if (motorVal == 'Y')
    {
        flipY();
    }
    else if (motorVal == 'Z')
    {
        flipZ();
    }
}
void flipX()
{
    xDirection *= -1;
    if (xDirection > 0)
    {
        Serial.println("RIGHT"); // TODO: Check Direction
    }
    else
    {
        Serial.println("LEFT");
    }
}
void flipY()
{
    yDirection *= -1;
    if (yDirection > 0)
    {
        Serial.println("FORWARDS"); // TODO: Check direction
    }
    else
    {
        Serial.println("BACKWARDS");
    }
}
void flipZ()
{
    zDirection *= -1;
    if (zDirection > 0)
    {
        Serial.println("UP");
    }
    else
    {
        Serial.println("DOWN");
    }
}

void stop()
{
    xMoving = false;
    yMoving = false;
    zMoving = false;
    Serial.println("Stopped");
}

void go()
{
    if (motorVal == 'X')
    {
        xMoving = true;
        Serial.println("X Moving");
    }
    else if (motorVal == 'Y')
    {
        yMoving = true;
        Serial.println("Y Moving");
    }
    else if (motorVal == 'Z')
    {
        zMoving = true;
        Serial.println("Z Moving");
    }
}

void step()
{
    if (xMoving)
    {
        xStepper.step(xDirection);
        //Serial.println("X");
    }
    else if (yMoving)
    {
        yStepper.step(yDirection);
        //Serial.println("Y");
    }
    else if (zMoving)
    {
        zStepper.step(zDirection);
        //Serial.println("Z");
    }
}
