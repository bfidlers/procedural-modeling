#include "point.h"

Point::Point() {
  x = 0;
  y = 0;
}

Point::Point(float x, float y) {
    this->x = x;
    this->y = y;
}

bool Point::operator==(const Point& other) const {
  return x == other.x && y == other.y;
}

std::ostream& operator <<(std::ostream& os, const Point& p) { return os << "(" << p.x << ", " << p.y << ")";
}
