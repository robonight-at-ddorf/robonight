/* 
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->	http://www.adafruit.com/products/1438
*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#include "sensor.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);
// You can also make another motor on port M2
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Adafruit Motorshield v2 - DC Motor test!");
  Serial.println(":)");
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  Serial.println("After AFMS.begin()");
  // Set the speed to start, from 0 (off) to 255 (max speed)
  rightMotor->setSpeed(150);
  leftMotor->setSpeed(150);

  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println("Speeds are set!");
  rightMotor->run(FORWARD);
  leftMotor->run(FORWARD);

  Serial.println("End of setup!");
  //myMotor->run(FORWARD);
  //myOtherMotor->run(FORWARD);
  // turn on motor
  //myMotor->run(RELEASE);
  //myOtherMotor->run(RELEASE);
}

const int SPEED_LOW = 25;
const int SPEED_HIGH = 150;

void moveLeft() {
  rightMotor->setSpeed(SPEED_LOW); 
  leftMotor->setSpeed(SPEED_HIGH);   
}

void moveRight() {
  rightMotor->setSpeed(SPEED_HIGH); 
  leftMotor->setSpeed(SPEED_LOW);   
}


void moveStraight() {
  rightMotor->setSpeed(SPEED_HIGH); 
  leftMotor->setSpeed(SPEED_HIGH);   
}

void loop() {
  Serial.println("In loop!");
  Direction direction = getDirection();

  switch(direction) {
    case LEFT:
      moveLeft();
      break;
    case STRAIGHT:
      moveStraight();
      break;
    case RIGHT:
      moveRight();
      break;
  }

  delay(25);
}
