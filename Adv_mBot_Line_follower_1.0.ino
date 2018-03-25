#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#include <MeMCore.h>

MeDCMotor motor_9(9);
MeDCMotor motor_10(10);		

void move(int direction, int speed)
{
      int leftSpeed = 0;
      int rightSpeed = 0;
      if(direction == 1){
        	leftSpeed = speed;
        	rightSpeed = speed;
      }else if(direction == 2){
        	leftSpeed = -speed;
        	rightSpeed = -speed;
      }else if(direction == 3){
        	leftSpeed = -speed;
        	rightSpeed = speed;
      }else if(direction == 4){
        	leftSpeed = speed;
        	rightSpeed = -speed;
      }
      motor_9.run((9)==M1?-(leftSpeed):(leftSpeed));
      motor_10.run((10)==M1?-(rightSpeed):(rightSpeed));
}
				
double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
void Button_Control();
double Turn_Counter;
double Turn_Speed;
double Turn_Counter_scale;
double Intensity_Red;
MeRGBLed rgbled_7(7, 7==7?2:4);
void Turn_right();
double Turn_More;
double Turn_Counter_limit;
double LED_Intensity;
double Left_Speed;
double Initial_Speed;
double Right_Speed;
double Turn_Speed_differential;
void Turn_left();
void Initialization();
double Intensity_Blue;
double Intensity_Green;
double Timeout;
void Go_straight();
void Continue_turn();
void Stop();
MeLineFollower linefollower_2(2);
double currentTime = 0;
double lastTime = 0;
double getLastTime(){
    	return currentTime = millis()/1000.0 - lastTime;
}


void Button_Control()
{
    if((0^(analogRead(A7)>10?0:1))){
        motor_9.run((9)==M1?-(0):(0));
        motor_10.run((10)==M1?-(0):(0));
        Turn_Counter = 0;
        Turn_Speed = (Turn_Counter) / (Turn_Counter_scale);
        while(!((1^(analogRead(A7)>10?0:1))))
        {
            _loop();
        }
        while(!((0^(analogRead(A7)>10?0:1))))
        {
            _loop();
            rgbled_7.setColor(0,0,0,0);
            rgbled_7.show();
            rgbled_7.setColor(2,Intensity_Red,0,0);
            rgbled_7.show();
            _delay(1);
            rgbled_7.setColor(0,0,0,0);
            rgbled_7.show();
            rgbled_7.setColor(1,Intensity_Red,0,0);
            rgbled_7.show();
            _delay(1);
        }
        while(!((1^(analogRead(A7)>10?0:1))))
        {
            _loop();
        }
    }
    
}

void Turn_right()
{
    Turn_Counter += Turn_More;
    
    if((Turn_Counter) > (Turn_Counter_limit)){
        Turn_Counter = Turn_Counter_limit;
    }
    
    Turn_Speed = (Turn_Counter) / (Turn_Counter_scale);
    
    LED_Intensity = Turn_Speed;
    
    rgbled_7.setColor(0,0,0,0);
    rgbled_7.show();
    
    rgbled_7.setColor(1,0,LED_Intensity,0);
    rgbled_7.show();
    
    Left_Speed = (Initial_Speed) + (Turn_Speed);
    
    Right_Speed = (Initial_Speed) - ((Turn_Speed) / (Turn_Speed_differential));
    
}

void Turn_left()
{
    Turn_Counter += Turn_More;
    
    if((Turn_Counter) > (Turn_Counter_limit)){
        Turn_Counter = Turn_Counter_limit;
    }
    
    Turn_Speed = (Turn_Counter) / (Turn_Counter_scale);
    
    LED_Intensity = Turn_Speed;
    
    rgbled_7.setColor(0,0,0,0);
    rgbled_7.show();
    
    rgbled_7.setColor(2,LED_Intensity,0,0);
    rgbled_7.show();
    
    Left_Speed = (Initial_Speed) - ((Turn_Speed) / (Turn_Speed_differential));
    
    Right_Speed = (Initial_Speed) + (Turn_Speed);
    
}

void Initialization()
{
    Intensity_Red = 16;
    
    Intensity_Blue = 16;
    
    Intensity_Green = 16;
    
    Initial_Speed = 60;
    
    Left_Speed = Initial_Speed;
    
    Right_Speed = Initial_Speed;
    
    Turn_Speed = 0;
    
    Turn_Counter = 0;
    
    Turn_Counter_limit = 1000;
    
    Turn_More = 5;
    
    Turn_Counter_scale = 10;
    
    Turn_Speed_differential = 1;
    
    Timeout = 5;
    
}

void Go_straight()
{
    Turn_Counter = 0;
    
    Turn_Speed = (Turn_Counter) / (Turn_Counter_scale);
    
    LED_Intensity = Turn_Speed;
    
    rgbled_7.setColor(0,0,0,LED_Intensity);
    rgbled_7.show();
    
    Left_Speed = Initial_Speed;
    
    Right_Speed = Initial_Speed;
    
}

void Continue_turn()
{
    LED_Intensity = Turn_Speed;
    
    rgbled_7.setColor(0,Intensity_Red,Intensity_Green,Intensity_Red);
    rgbled_7.show();
    
}

void Stop()
{
    motor_9.run((9)==M1?-(0):(0));
    
    motor_10.run((10)==M1?-(0):(0));
    
    Turn_Counter = 0;
    
    Turn_Speed = (Turn_Counter) / (Turn_Counter_scale);
    
    while(!((1^(analogRead(A7)>10?0:1))))
    {
        _loop();
        while(!((0^(analogRead(A7)>10?0:1))))
        {
            _loop();
        }
        rgbled_7.setColor(0,0,0,0);
        rgbled_7.show();
        rgbled_7.setColor(2,Intensity_Red,0,0);
        rgbled_7.show();
        _delay(1);
        rgbled_7.setColor(0,0,0,0);
        rgbled_7.show();
        rgbled_7.setColor(1,Intensity_Red,0,0);
        rgbled_7.show();
        _delay(1);
    }
    
    while(!((0^(analogRead(A7)>10?0:1))))
    {
        _loop();
    }
    
    while(!((1^(analogRead(A7)>10?0:1))))
    {
        _loop();
    }
    
}


void setup(){
    Initialization();
    
    pinMode(A7,INPUT);
}

void loop(){
    
    Button_Control();
    if(((true&&(1?(linefollower_2.readSensors()&2):!(linefollower_2.readSensors()&2)))) && ((true&&(1?(linefollower_2.readSensors()&1):!(linefollower_2.readSensors()&1))))){
        if((getLastTime()) > (Timeout)){
            Stop();
        }
        Continue_turn();
    }else{
        if(((true&&(0?(linefollower_2.readSensors()&2):!(linefollower_2.readSensors()&2)))) && ((true&&(1?(linefollower_2.readSensors()&1):!(linefollower_2.readSensors()&1))))){
            lastTime = millis()/1000.0;
            Turn_left();
        }
        if(((true&&(1?(linefollower_2.readSensors()&2):!(linefollower_2.readSensors()&2)))) && ((true&&(0?(linefollower_2.readSensors()&1):!(linefollower_2.readSensors()&1))))){
            lastTime = millis()/1000.0;
            Turn_right();
        }
        if(((true&&(0?(linefollower_2.readSensors()&2):!(linefollower_2.readSensors()&2)))) && ((true&&(0?(linefollower_2.readSensors()&1):!(linefollower_2.readSensors()&1))))){
            lastTime = millis()/1000.0;
            Go_straight();
        }
        motor_9.run((9)==M1?-(Left_Speed):(Left_Speed));
        motor_10.run((10)==M1?-(Right_Speed):(Right_Speed));
    }
    
    _loop();
}

void _delay(float seconds){
    long endTime = millis() + seconds * 1000;
    while(millis() < endTime)_loop();
}

void _loop(){
    
}

