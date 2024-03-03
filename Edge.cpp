#include "Edge.h"

Edge::Edge(EdgeLabel label) : label(label) {
}
Edge::Edge(int angle) {
  label.angle = angle;
}
Edge::Edge(int angle, std::string left, std::string right) {
  EdgeLabel l(angle, left, right);
  label = l;
}
Edge::Edge(Point p1, Point p2) {
  label.angle = std::round(atan2(p2.y - p1.y, p2.x - p1.x) * 180 / M_PI);
  origin = p1;
}
Edge::Edge(Point p1, Point p2, std::string left, std::string right) {
  label.leftFace = left;
  label.rightFace = right;
  label.angle = std::round(atan2(p2.y - p1.y, p2.x - p1.x) * 180 / M_PI);
  origin = p1;
}

EdgeLabel Edge::get_primitive_edge(Point p) const {
  if (origin == p) {
    return label;
  } else {
    return label.get_inverse();
  }
}

std::ostream& operator <<(std::ostream& os, const Edge& e) {
  os << "Edge with label " << e.label;
  os << ", from origin " << e.origin << std::endl;
  return os;
}
