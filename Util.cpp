#include "util.h"

double roundToDigits(double value, int digits) {
  double scale = std::pow(10.0, digits);
  return std::round(value * scale) / scale;
}

double sine(int angle) {
  double result = sin(angle * M_PI/180);
  return roundToDigits(result, 8);
}

double cosine(int angle) {
  double result = cos(angle * M_PI/180);
  return roundToDigits(result, 8);
}

int inverseAngle(int angle) {
  if (angle == 0) {
    return 180;
  } else if (angle > 0) {
    return angle - 180;
  } else {
    return angle + 180;
  }
}

