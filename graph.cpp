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
  return os << "Face with id: " << f.id << std::endl;
}

void load_graph() {
  Face f("test");
  Face f2;
  std::cout << f << std::endl;
  std::cout << f2 << std::endl;

  std::cout << "Graph loaded!" << std::endl;
}
