#ifndef PROCEDURAL_MODELING_VERTEX_H
#define PROCEDURAL_MODELING_VERTEX_H

#include "Point.h"
#include "Edge.h"
#include "Primitive.h"

#include <iostream>
#include <vector>

class Vertex {
public:
  Point pos;
  std::vector<Edge> edges;

  Vertex(Point p);
  Vertex(float x, float y);

  void add(Edge &edge);

  Primitive generate_primitive() const;
};

std::ostream& operator <<(std::ostream& os, const Vertex& v);

#endif //PROCEDURAL_MODELING_VERTEX_H
