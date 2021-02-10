#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

//our L298N control pins
const int RightMotorForward = 7;
const int RightMotorBackward = 6;
const int LeftMotorForward = 5;
const int LeftMotorBackward = 4;

//sensor pins
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2

#define maximum_distance 200
boolean goesForward = false;
int distance = 100;
int prevTurn=1;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name


void setup(){
  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  
  servo_motor.attach(10); //our servo pin

  servo_motor.write(115);
  delay(2000);
  distance = readPing();
}

void loop(){
  int distanceRight = 0;
  int distanceLeft = 0;
  delay(50);
  if (distance <= 35){
    moveStop();
    delay(300);
    moveBackward();
    delay(400);
    moveStop();
    delay(300);
    distanceRight = lookRight();
    delay(300);
    distanceLeft = lookLeft();
    delay(300);

    if (prevTurn==1){
      if(distanceRight >= 25){
       turnRight(400);
       moveStop();
      }
      else {
       prevTurn=0;
       turnLeft(400);
       moveStop();
      }
    }
    else{
      if(distanceLeft >= 25)
      {
       turnLeft(400);
       moveStop(); 
      }
      else 
      {
       prevTurn=1;
       turnRight(400);
       moveStop();
      }
       
  }
  }
  else{
    moveForward(); 
  }
    distance = readPing();
}

int lookRight(){  
  servo_motor.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int lookLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(115);
  return distance;
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  return cm;
}

void moveStop(){
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
}

void moveForward(){

    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorForward, HIGH);

    digitalWrite(RightMotorBackward, LOW);
    digitalWrite(LeftMotorBackward, LOW); 
}

void moveBackward(){

  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorBackward, HIGH);

  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  
}

void turnRight(int d){
  
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(LeftMotorForward, HIGH);
  
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  
  delay(d);
  moveStop();
}

void turnLeft(int d){
  
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, HIGH);
  
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorForward, LOW);

  delay(d);
  moveStop();
}
