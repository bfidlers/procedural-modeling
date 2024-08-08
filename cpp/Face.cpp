#include "Face.h"

Face::Face() {
  id = "0";
}
Face::Face(std::string s) {
  id = s;
}

std::ostream& operator <<(std::ostream& os, const Face& f) {
  return os << f.id;
}
