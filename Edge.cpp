#include "Edge.h"
#include <OpenGL/gl.h>

Edge::Edge(Point p1, Point p2) {
  label.angle = std::round(atan2(p2.y - p1.y, p2.x - p1.x) * 180 / M_PI);
  origin = p1;
  dest = p2;
}
Edge::Edge(Point p1, Point p2, std::string left, std::string right) {
  label.leftFace = left;
  label.rightFace = right;
  label.angle = std::round(atan2(p2.y - p1.y, p2.x - p1.x) * 180 / M_PI);
  origin = p1;
  dest = p2;
}

EdgeLabel Edge::get_primitive_edge(Point p) const {
  if (origin == p) {
    return label;
  } else {
    return label.get_inverse();
  }
}

void Edge::draw() const {
  glBegin(GL_LINES);
  glVertex3f(origin.x, origin.y, 0);
  glVertex3f(dest.x, dest.y, 0);
  glEnd();
}

std::ostream& operator <<(std::ostream& os, const Edge& e) {
  os << "Edge with label " << e.label;
  os << ", from origin " << e.origin << std::endl;
  return os;
}
