#include "Point.h"

Point::Point() {
  x = 0;
  y = 0;
  z = 0;
}

Point::Point(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

bool Point::operator==(const Point& other) const {
  return x == other.x && y == other.y;
}

std::ostream& operator <<(std::ostream& os, const Point& p) { return os << "(" << p.x << ", " << p.y << ")";
}
