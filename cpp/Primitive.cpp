#include "Primitive.h"
#include <OpenGL/gl.h>

Primitive::Primitive(Point p) {
  pos = p;
}

void Primitive::add(EdgeLabel edge) {
  half_edges.push_back(edge);
}

void Primitive::draw() const {
  for (const EdgeLabel &edge: half_edges) {
    glBegin(GL_LINES);
    glVertex3f(pos.x, pos.y, 0);
    glVertex3f(pos.x + cos(edge.angle * M_PI / 180) * 0.25, pos.y + sin(edge.angle * M_PI / 180) * 0.25, 0);
    glEnd();
  }
}

std::ostream& operator <<(std::ostream& os, const Primitive& p) {
  os << "Primitive: " << p.pos << std::endl;
  for (const EdgeLabel& e: p.half_edges) {
    os << e << std::endl;
  }
  return os;
}
