
#include <Arduino.h>
#include "car_controller.h"

String directionToString(Direction direction) {
  switch(direction) {
    case LEFT:
      return "Left";
    case STRAIGHT:
      return "Straight";
    case RIGHT:
      return "Right";
    default:
      return "Unknown";
  }
}

Direction getDirection2(int rightValue, int leftValue){
  bool leftOnBlack = leftValue < threshold;
  bool rightOnBlack = rightValue < threshold;

  if (leftOnBlack && rightOnBlack) {
    return STRAIGHT;
  }
  if (leftOnBlack) {
    return LEFT;
  }
  if (rightOnBlack) {
    return RIGHT;
  }
  return STRAIGHT;
}

Direction getDirection() {
  int rightValue = analogRead(input_right);
  int leftValue = analogRead(input_left);

  Direction direction = getDirection2(rightValue, leftValue);
  Serial.print("Direction: ");
  Serial.println(directionToString(direction));
  return direction;
}
