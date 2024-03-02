#include "Vertex.h"

Vertex::Vertex(Point p) {
  pos = p;
}
Vertex::Vertex(float x, float y) {
  pos.x = x;
  pos.y = y;
}

void Vertex::add(Edge &edge) {
  edges.push_back(edge);
}

Primitive Vertex::generate_primitive() const {
  Primitive p(pos);
  for (const Edge &e: edges) {
    p.add(e.get_primitive_edge(pos));
  }
  return p;
}

std::ostream& operator <<(std::ostream& os, const Vertex& v) {
  os << "Vertex with position: " << v.pos << std::endl;
  os << "and edges: " << std::endl;
  for (const Edge& edge: v.edges) {
    os << edge;
  }
  return os;
}
