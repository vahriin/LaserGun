#include <Servo.h>

const short int motorInput[4] = {13,5,6,7};
Servo servo;
const short int redLed = 4;
const short int greenLed = 3;
const short int laser = 8;

const short int joystickX = A0;
const short int joystickY = A1;
const short int joystickButton = A2;

int *coordX = new int; 
int *coordY = new int;
boolean *button;

void setup()
{
    Serial.begin(9600); 
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
    getJoystick(coordX, coordY, button);
    if (*coordX != 0)
        motorControl(*coordX);
    else
        delay(10);
    if (*coordY != 0)
        servoControl(*coordY);
}

void getJoystick(int *coordX, int *coordY, boolean *button)
{
    *coordX = analogRead(joystickX) / 128;
    *coordY = analogRead(joystickY) / 128;
    if (*coordX > 3)
        *coordX -= 4;
    else
        *coordX -= 3;
    //Serial.println(*coordX);
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

bool motorControl(short int speed)
{
    static short int degree = 0;
    if (degree < 300 && speed > 0)
    {
        motorForward(4-speed);
        degree++;
        return true;
    }
    else if (degree > -300 && speed < 0)
    {
        motorBack(4+speed);
        degree--;
        return true;
    }
    return false;
}

void servoControl(short int speed)
{
    static short int degree = 900;
    degree += speed;
    if (degree <= 1800 && degree >= 0)
    {
        servo.write(degree / 10);
    }
    else 
    {
        if (degree >= 1800)
            degree = 1800;
        else
            degree = 50;
    }
}



//very long shitcode

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

