#ifndef PROCEDURAL_MODELING_UTIL_H
#define PROCEDURAL_MODELING_UTIL_H

#include <iostream>

double roundToDigits(double value, int digits);

double sine(int angle);

double cosine(int angle);

int inverseAngle(int angle);

std::string inverseEdgeLabelId(const std::string& id);

#endif //PROCEDURAL_MODELING_UTIL_H
