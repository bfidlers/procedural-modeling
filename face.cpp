#include "Face.h"

Face::Face() {
  id = "blank";
}
Face::Face(std::string s) {
  id = s;
}

std::ostream& operator <<(std::ostream& os, const Face& f) {
  return os << "Face with id: " << f.id;
}
