#ifndef PROCEDURAL_MODELING_INPUT_VERTEX_H
#define PROCEDURAL_MODELING_INPUT_VERTEX_H

#include "Point.h"
#include "InputEdge.h"
#include "Primitive.h"

#include <iostream>
#include <vector>

class InputVertex {
public:
  Point pos;
  std::vector<InputEdge> edges;

  InputVertex(Point p);
  InputVertex(float x, float y);

  void add(InputEdge &edge);

  Primitive generate_primitive() const;
};

std::ostream& operator <<(std::ostream& os, const InputVertex& v);

#endif //PROCEDURAL_MODELING_INPUT_VERTEX_H
