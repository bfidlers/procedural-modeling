#ifndef PROCEDURAL_MODELING_POINT_H
#define PROCEDURAL_MODELING_POINT_H

#include <iostream>

class Point {
public:
  float x;
  float y;
  float z;

  Point();
  Point(float x, float y, float z = 0);

  bool operator==(const Point& other) const;
};

std::ostream& operator <<(std::ostream& os, const Point& p);

#endif //PROCEDURAL_MODELING_POINT_H
