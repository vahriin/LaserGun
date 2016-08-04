#include <Servo.h>

const short int motorInput[4] = {13,5,6,7};
Servo servo;
const short int redLed = 4;
const short int greenLed = 3;
const short int laser = 8;

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
    pinMode(laser, OUTPUT);
    
    pinMode(joystickX, INPUT);
    pinMode(joystickY, INPUT);
    pinMode(joystickButton, INPUT);
}

void loop()
{
    
}

void getJoystick(short int *coordX, short int *coordY, bool *button)
{
    *coordX = analogRead(joystickX) / 128;
    *coordY = analogRead(joystickY) / 128;
    
    if (*coordX > 3)
        *coordX -= 4;
    else
        *coordX -=3;
    
    if (*coordY > 3)
        *coordY -= 4;
    else
        *coordY -=3;
    
    *button = (bool *)analogRead(joystickButton);
}

bool laserShot(void)
{
    digitalWrite(laser, HIGH);
    delay(500);
    digitalWrite(laser, LOW);
    return true;
}

bool motorWork(short int speed)
{
    static short int degree = 0;
    if (degree < 180 && degree > -180)
    {
        if (speed > 0)
        {
            motorForward(4-speed);
            degree++;
        }
        else if (speed < 0)
        {
            motorBack(4+speed);
            degree--;
        }
        else
            return false;
        return true;
    }
    else
        return false;
}





void motorForward(short int speed)
{
    digitalWrite(motorInput[0], LOW); 
    digitalWrite(motorInput[1], LOW ); 
    digitalWrite(motorInput[2], HIGH ); 
    digitalWrite(motorInput[3], HIGH );
    delay(speed);

    digitalWrite(motorInput[0], LOW ); 
    digitalWrite(motorInput[1], LOW ); 
    digitalWrite(motorInput[2], HIGH ); 
    digitalWrite(motorInput[3], LOW );
    delay(speed);

    digitalWrite(motorInput[0], LOW ); 
    digitalWrite(motorInput[1], HIGH ); 
    digitalWrite(motorInput[2], HIGH ); 
    digitalWrite(motorInput[3], LOW );
    delay(speed);

    digitalWrite(motorInput[0], LOW ); 
    digitalWrite(motorInput[1], HIGH ); 
    digitalWrite(motorInput[2], LOW ); 
    digitalWrite(motorInput[3], LOW );
    delay(speed);

    digitalWrite(motorInput[0], HIGH ); 
    digitalWrite(motorInput[1], HIGH ); 
    digitalWrite(motorInput[2], LOW ); 
    digitalWrite(motorInput[3], LOW );
    delay(speed);

    digitalWrite(motorInput[0], HIGH ); 
    digitalWrite(motorInput[1], LOW ); 
    digitalWrite(motorInput[2], LOW ); 
    digitalWrite(motorInput[3], LOW );
    delay(speed);

    digitalWrite(motorInput[0], HIGH ); 
    digitalWrite(motorInput[1], LOW ); 
    digitalWrite(motorInput[2], LOW ); 
    digitalWrite(motorInput[3], HIGH );
    delay(speed);

    digitalWrite(motorInput[0], LOW ); 
    digitalWrite(motorInput[1], LOW ); 
    digitalWrite(motorInput[2], LOW ); 
    digitalWrite(motorInput[3], HIGH );
    delay(speed);
}

void motorBack(short int speed)
{    
    digitalWrite(motorInput[0], LOW ); 
    digitalWrite(motorInput[1], LOW ); 
    digitalWrite(motorInput[2], LOW ); 
    digitalWrite(motorInput[3], HIGH );
    delay(speed);
    
    digitalWrite(motorInput[0], HIGH ); 
    digitalWrite(motorInput[1], LOW ); 
    digitalWrite(motorInput[2], LOW ); 
    digitalWrite(motorInput[3], HIGH );
    delay(speed);
    
    digitalWrite(motorInput[0], HIGH ); 
    digitalWrite(motorInput[1], LOW ); 
    digitalWrite(motorInput[2], LOW ); 
    digitalWrite(motorInput[3], LOW );
    delay(speed);
    
    digitalWrite(motorInput[0], HIGH ); 
    digitalWrite(motorInput[1], HIGH ); 
    digitalWrite(motorInput[2], LOW ); 
    digitalWrite(motorInput[3], LOW );
    delay(speed);
    
    digitalWrite(motorInput[0], LOW ); 
    digitalWrite(motorInput[1], HIGH ); 
    digitalWrite(motorInput[2], LOW ); 
    digitalWrite(motorInput[3], LOW );
    delay(speed);
    
    digitalWrite(motorInput[0], LOW ); 
    digitalWrite(motorInput[1], HIGH ); 
    digitalWrite(motorInput[2], HIGH ); 
    digitalWrite(motorInput[3], LOW );
    delay(speed);
    
    digitalWrite(motorInput[0], LOW ); 
    digitalWrite(motorInput[1], LOW ); 
    digitalWrite(motorInput[2], HIGH ); 
    digitalWrite(motorInput[3], LOW );
    delay(speed);
    
    digitalWrite(motorInput[0], LOW); 
    digitalWrite(motorInput[1], LOW ); 
    digitalWrite(motorInput[2], HIGH ); 
    digitalWrite(motorInput[3], HIGH );
    delay(speed);
}

