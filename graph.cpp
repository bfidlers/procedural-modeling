#include <iostream>
#include <string>

struct Face {
  std::string id;

  Face(std::string s) {
    id = s;
  }
};

std::ostream& operator <<(std::ostream& os, const Face& f) {
  return os << "Face with id: " << f.id << std::endl;
}

void load_graph() {
  Face f("test");
  std::cout << f << std::endl;

  std::cout << "Graph loaded!" << std::endl;
}
