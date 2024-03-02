#ifndef PROCEDURAL_MODELING_POINT_H
#define PROCEDURAL_MODELING_POINT_H

#include <iostream>

class Point {
public:
  float x;
  float y;

  Point();
  Point(float x, float y);

  bool operator==(const Point& other) const;
};

std::ostream& operator <<(std::ostream& os, const Point& p);

#endif //PROCEDURAL_MODELING_POINT_H
