#include <Servo.h>

const short int motorInput[4] = {13,5,6,7}; //управление мотором
Servo servo; // управление сервомотором
const short int redLed = 3; //индикатор перезарядки
const short int yellowLed = 4; //индикатор готовности к стрельбе
const short int laser = 8; //индикатор выстрела

const short int joystickX = A0;
const short int joystickY = A1;
const short int joystickButton = A2;

int *coordX = new int; 
int *coordY = new int;
boolean *button = new boolean;
boolean gunReady = true;

void setup()
{
    servo.attach(2);
    
    for (int i = 0; i < 4; i++)
    {
        pinMode(motorInput[i], OUTPUT);
    }
    pinMode(redLed, OUTPUT);
    pinMode(yellowLed, OUTPUT);
    pinMode(laser, OUTPUT);
    
    pinMode(joystickX, INPUT);
    pinMode(joystickY, INPUT);
    pinMode(joystickButton, INPUT_PULLUP);
}

void loop()
{
    getJoystick(coordX, coordY, button);
    
    // дабы не делать лишних вызовов функций
    if (*coordX != 0) 
        motorControl(*coordX);
    else
        delay(10); // для уравнивания скорости
    if (*coordY != 0)
        servoControl(*coordY);
        
    if(!(*button) || (!gunReady))
        gunReady = gunGuard(*button);
    
}

//get section

void getJoystick(int *coordX, int *coordY, boolean *button)
{
    *coordX = analogRead(joystickX) / 128; //оставляем значения 0-7
    *coordY = analogRead(joystickY) / 128;
    if (*coordX > 3)
        *coordX -= 4; //приводим к значениям -3 - 3
    else
        *coordX -= 3;
    if (*coordY > 3)
        *coordY -= 4;
    else
        *coordY -=3;
    
    *button = (boolean*)digitalRead(joystickButton);
}

//laser section

boolean gunGuard(boolean shot)
{
    const int reloadTime = 8000;
    static unsigned long timeShot = 0;
    if(!(shot) && (millis() - timeShot) > reloadTime) //нажата кнопка и орудие перезарядилось
    {
        digitalWrite(yellowLed, LOW); //выключим индикатор готовности к стрельбе
        digitalWrite(redLed, HIGH); //включим индикатор перезарядки
        laserShot(); //стреляем
        timeShot = millis();
        return false;
    }
    else if (shot && (millis() - timeShot) > reloadTime) //кнопка не нажата, но орудие перезарядилось
    {
        digitalWrite(redLed, LOW); //выключим индикатор перезарядки
        digitalWrite(yellowLed, HIGH); //включим индикатор готовности к стрельбе
        return true;
    }
    else if (!(shot) && (millis() - timeShot) < reloadTime) //орудие не перезарядилось, но кнопка нажата
    {
        digitalWrite(yellowLed, HIGH); //моргнем, чтобы показать, что юзер дурень.
        delay(50);
        digitalWrite(yellowLed, LOW);
        return false;
    }
    else 
    {
        return false;
    }
}


void laserShot(void)
{
    digitalWrite(laser, HIGH);
    delay(500);
    digitalWrite(laser, LOW);
}


//move section

void motorControl(short int speed)
{
    static short int degree = 0;
    if (degree < 300 && speed > 0)
    {
        motorForward(4-speed); //разворачиваем значение
        degree++;
    }
    else if (degree > -300 && speed < 0)
    {
        motorBack(4+speed);
        degree--;
    }
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

void motorForward(short int speed) // чем больше speed, тем медленнее едем
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

