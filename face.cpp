#include "face.h"

face::face() {
  id = "blank";
}
face::face(std::string s) {
  id = s;
}

std::ostream& operator <<(std::ostream& os, const face& f) {
  return os << "face with id: " << f.id;
}
