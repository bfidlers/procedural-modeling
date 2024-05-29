#include "InputVertex.h"

InputVertex::InputVertex(Point p) {
  pos = p;
}
InputVertex::InputVertex(float x, float y) {
  pos.x = x;
  pos.y = y;
}

void InputVertex::add(InputEdge &edge) {
  edges.push_back(edge);
}

Primitive InputVertex::generate_primitive() const {
  Primitive p(pos);
  for (const InputEdge &e: edges) {
    p.add(e.get_primitive_edge(pos));
  }
  return p;
}

std::ostream& operator <<(std::ostream& os, const InputVertex& v) {
  os << "Vertex with position: " << v.pos << std::endl;
  os << "and edges: " << std::endl;
  for (const InputEdge& edge: v.edges) {
    os << edge;
  }
  return os;
}
