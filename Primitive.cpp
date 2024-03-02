#include "Primitive.h"

Primitive::Primitive(Point p) {
  pos = p;
}

void Primitive::add(EdgeLabel edge) {
  half_edges.push_back(edge);
}

std::ostream& operator <<(std::ostream& os, const Primitive& p) {
  os << "Primitive: " << p.pos << std::endl;
  for (const EdgeLabel& e: p.half_edges) {
    os << e << std::endl;
  }
  return os;
}
