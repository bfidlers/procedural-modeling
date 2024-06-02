#ifndef PROCEDURAL_MODELING_UTIL_H
#define PROCEDURAL_MODELING_UTIL_H

#include <iostream>

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

#endif //PROCEDURAL_MODELING_UTIL_H
