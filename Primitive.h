#ifndef PROCEDURAL_MODELING_PRIMITIVE_H
#define PROCEDURAL_MODELING_PRIMITIVE_H

#include "Point.h"
#include "EdgeLabel.h"

#include <iostream>
#include <vector>

class Primitive {
public:
  Point pos;
  std::vector<EdgeLabel> half_edges;

  Primitive(Point p);

  void add(EdgeLabel edge);
};

std::ostream& operator <<(std::ostream& os, const Primitive& p);

#endif //PROCEDURAL_MODELING_PRIMITIVE_H
