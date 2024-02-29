#include <iostream>
#include <string>

struct Face {
  std::string id;

  Face() {
    id = "blank";
  }
  Face(std::string s) {
    id = s;
  }
};

std::ostream& operator <<(std::ostream& os, const Face& f) {
  return os << "Face with id: " << f.id;
}

struct EdgeLabel {
  Face leftFace;
  Face rightFace;
  float angle;

  EdgeLabel(float a) {
    angle = a;
  }
  EdgeLabel(float a, std::string left, std::string right) {
    angle = a;
    leftFace.id = left;
    rightFace.id = right;
  }
  EdgeLabel(float a, Face left, Face right) {
    angle = a;
    leftFace = left;
    leftFace = right;
  }
};

std::ostream& operator <<(std::ostream& os, const EdgeLabel& e) {
  return os << "leftFace: " << e.leftFace << std::endl
    << "rightFace: " << e.rightFace << std::endl
    << "angle:" << e.angle << std::endl;
}

void load_graph() {
  EdgeLabel f(90);
  EdgeLabel f2(90, "1", "2");
  std::cout << f << std::endl;
  std::cout << f2 << std::endl;

  std::cout << "Graph loaded!" << std::endl;
}
