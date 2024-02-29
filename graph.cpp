#include <iostream>
#include <string>
#include <vector>

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

struct Point {
  float x;
  float y;

  Point() {
    x = 0;
    y = 0;
  }
  Point(float x, float y) {
    this->x = x;
    this->y = y;
  }
};

std::ostream& operator <<(std::ostream& os, const Point& p) {
  return os << "(" << p.x << ", " << p.y << ")";
}

struct Graph {
  std::vector<Point> vertices;

  Graph(std::vector<Point> &v) {
    vertices = v;
  }
};

std::ostream& operator <<(std::ostream& os, const Graph& g) {
  os << "Graph containing the following:" << std::endl;
  os << "Vertices:" << std::endl;
  for (const Point& v: g.vertices) {
    os << v << std::endl;
  }
  return os;
}

void load_graph() {
  Point p(1,2);
  Point p2;
  std::vector<Point> v;
  v.push_back(p);
  v.push_back(p2);
  Graph g(v);
  std::cout << g << std::endl;

  std::cout << "Graph loaded!" << std::endl;
}
