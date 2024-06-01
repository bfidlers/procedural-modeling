#include "InputEdge.h"
#include <OpenGL/gl.h>

InputEdge::InputEdge(Point p1, Point p2) {
  label.angle = std::round(atan2(p2.y - p1.y, p2.x - p1.x) * 180 / M_PI);
  origin = p1;
  dest = p2;
}
InputEdge::InputEdge(Point p1, Point p2, std::string left, std::string right) {
  label.leftFace = left;
  label.rightFace = right;
  label.angle = std::round(atan2(p2.y - p1.y, p2.x - p1.x) * 180 / M_PI);
  origin = p1;
  dest = p2;
}

EdgeLabel InputEdge::get_primitive_edge(Point p) const {
  if (origin == p) {
    return label;
  } else {
    return label.get_inverse();
  }
}

void InputEdge::draw() const {
  glBegin(GL_LINES);
  glVertex3f(origin.x, origin.y, origin.z);
  glVertex3f(dest.x, dest.y, dest.z);
  glEnd();
}

std::ostream& operator <<(std::ostream& os, const InputEdge& e) {
  os << "Edge with label " << e.label;
  os << ", from origin " << e.origin << std::endl;
  return os;
}
