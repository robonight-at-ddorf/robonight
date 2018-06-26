
const int input_left = 3;   // Yellow cable
const int input_right = 4;  // Blue cable

const int threshold = 600;

enum Direction {
  LEFT,
  STRAIGHT,
  RIGHT,
  UNKNOWN
};

Direction getDirection();
