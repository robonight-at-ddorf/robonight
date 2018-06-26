#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#include "car_controller.h"
#include "distance/sensor.h"
#include "distance/controller.h"

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);

const int FAKE_VCC = 4;

const Sensor sensor(8, 9);

const int SPEED_LOW = 150;
const int SPEED_HIGH = 254;

unsigned int moveUntil = 0;
Direction toMove;


void setup() {
  Serial.begin(9600);
  Serial.println("Hello I am Tankie. I will search you. And then run away.");
  Serial.println(":)");
  AFMS.begin();  

  rightMotor->setSpeed(SPEED_HIGH);
  leftMotor->setSpeed(SPEED_HIGH);

  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);

  pinMode(FAKE_VCC, OUTPUT);
  digitalWrite(FAKE_VCC, true);
}
void moveLeft() {
  rightMotor->run(FORWARD);
  leftMotor->run(BACKWARD);
  rightMotor->setSpeed(SPEED_LOW); 
  leftMotor->setSpeed(SPEED_LOW);   
}

void moveRight() {
  rightMotor->run(BACKWARD);
  leftMotor->run(FORWARD);
  rightMotor->setSpeed(SPEED_LOW); 
  leftMotor->setSpeed(SPEED_LOW);   
}


void moveStraight() {
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
  rightMotor->setSpeed(SPEED_HIGH); 
  leftMotor->setSpeed(SPEED_HIGH);   
}
void moveStraightSlow() {
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);
  rightMotor->setSpeed(SPEED_LOW); 
  leftMotor->setSpeed(SPEED_LOW);   
}

void loop() {

  unsigned int now = millis();
  // get time in ms since last run
  if (now < moveUntil) {
    switch (toMove) {
      case LEFT:
        moveLeft();
        break;
      case RIGHT:
        moveRight();
        break;
      default:
        moveUntil = now-1;
        break;
    }

    return;
  }

  Range range = convert( sensor.readDistance() );
  switch(range) {
    case OK:
      moveStraight();
      break;
    case WARN:
       moveStraightSlow();
       break;
    case ERROR:
      moveUntil = now + random(100, 2000);
      toMove = random(0, 2) > 0 ? LEFT : RIGHT;
      break;
  }
}
