#include "graph.h"

#include <iostream>
#include <string>
#include <vector>

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
  EdgeLabel get_inverse() {
    EdgeLabel inverse(-angle, rightFace, leftFace);
    return inverse;
  }
};

std::ostream& operator <<(std::ostream& os, const EdgeLabel& e) {
  return os << "leftFace: " << e.leftFace << std::endl
    << "rightFace: " << e.rightFace << std::endl
    << "angle:" << e.angle << std::endl;
}

struct Edge{
  EdgeLabel label = EdgeLabel(0);
  Point origin;

  Edge(EdgeLabel label) : label(label) {
  }
  Edge(float angle) {
    label.angle = angle;
  }
  Edge(float a, std::string left, std::string right) {
    EdgeLabel l(a, left, right);
    label = l;
  }
  Edge(Point p1, Point p2) {
    label.angle = static_cast<float>(atan2(p2.y - p1.y, p2.x - p1.x) * 180 / M_PI);
    origin = p1;
  }
};

std::ostream& operator <<(std::ostream& os, const Edge& e) {
  os << "Edge containing the following information:" << std::endl << e.label;
  os << "from origin: " << e.origin << std::endl;
  return os;
}

struct Vertex {
  Point pos;
  std::vector<Edge> edges;

  Vertex(Point p) {
    pos = p;
  }
  Vertex(float x, float y) {
    pos.x = x;
    pos.y = y;
  }

  void add(Edge &edge) {
    edges.push_back(edge);
  }
};

std::ostream& operator <<(std::ostream& os, const Vertex& v) {
  os << "Vertex with position: " << v.pos << std::endl;
  os << "and edges: " << std::endl;
  for (const Edge& edge: v.edges) {
    os << edge;
  }
  return os;
}

struct Graph {
  std::vector<Vertex> vertices;

  Graph() = default;

  void add(Vertex &vertex) {
    vertices.push_back(vertex);
  }
};

std::ostream& operator <<(std::ostream& os, const Graph& g) {
  os << "Graph containing the following:" << std::endl;
  os << "Vertices:" << std::endl;
  for (const Vertex& v: g.vertices) {
    os << v << std::endl;
  }
  return os;
}

void load_graph() {
  Graph g;

  Vertex v1(0,0);
  Vertex v2(1,0);
  Vertex v3(1,1);
  Vertex v4(0,1);

  Edge e1(v1.pos, v2.pos);
  Edge e2(v2.pos, v3.pos);
  Edge e3(v3.pos, v4.pos);
  Edge e4(v4.pos, v1.pos);

  v1.add(e1);
  v1.add(e4);
  v2.add(e1);
  v2.add(e2);
  v3.add(e2);
  v3.add(e3);
  v4.add(e3);
  v4.add(e4);

  g.add(v1);
  g.add(v2);
  g.add(v3);
  g.add(v4);

  std::cout << g << std::endl;
  std::cout << "Graph loaded!" << std::endl;
}
