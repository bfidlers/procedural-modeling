#include "input.h"
#include "Point.h"
#include "Edge.h"
#include "Primitive.h"

#include <iostream>
#include <vector>

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

  Primitive generate_primitive() const {
    Primitive p(pos);
    for (const Edge &e: edges) {
      p.add(e.get_primitive_edge(pos));
    }
    return p;
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

  void split_primitives(std::vector<Primitive>& primitives) {
    for (const Vertex& v: vertices) {
      primitives.push_back(v.generate_primitive());
    }
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

void test() {
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

  std::vector<Primitive> primitives;
  g.split_primitives(primitives);
  for (const Primitive& p: primitives) {
    std::cout << p << std::endl;
  }
}