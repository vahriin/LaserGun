#include <Servo.h>

const short int motorInput[4] = {5,6,7,13};
Servo servo;
const short int redLed = 4;
const short int greenLed = 3;
const short int joystickX = A0;
const short int joystickY = A1;
const short int joystickButton = A2;

void setup()
{
    servo.attach(2);
    
    for (int i = 0; i < 4; i++)
    {
        pinMode(motorInput[i], OUTPUT);
    }
    pinMode(redLed, OUTPUT);
    pinMode(greenLed, OUTPUT);
    
    pinMode(joystickX, INPUT);
    pinMode(joystickY, INPUT);
    pinMode(joystickButton, INPUT);
}

void loop()
{
    
}
