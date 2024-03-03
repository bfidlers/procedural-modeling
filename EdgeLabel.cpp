#include "EdgeLabel.h"

EdgeLabel::EdgeLabel() {
  angle = 0;
}
EdgeLabel::EdgeLabel(int a) {
  angle = a;
}
EdgeLabel::EdgeLabel(int a, std::string left, std::string right) {
  angle = a;
  leftFace.id = left;
  rightFace.id = right;
}
EdgeLabel::EdgeLabel(int a, Face left, Face right) {
  angle = a;
  leftFace = left;
  rightFace = right;
}

EdgeLabel EdgeLabel::get_inverse() const {
  int new_angle = angle > 0 ? angle - 180 : angle + 180;
  EdgeLabel inverse(new_angle, rightFace, leftFace);
  return inverse;
}

std::ostream& operator <<(std::ostream& os, const EdgeLabel& e) {
  return os << "(" << e.leftFace << ", " << e.rightFace << ", " << e.angle << ")";
}
