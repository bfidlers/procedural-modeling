#ifndef PROCEDURAL_MODELING_INPUT_EDGE_H
#define PROCEDURAL_MODELING_INPUT_EDGE_H

#include "Point.h"
#include "EdgeLabel.h"

#include <iostream>
#include <string>

class InputEdge {
public:
  EdgeLabel label = EdgeLabel(0);
  Point origin;
  Point dest;

  InputEdge(Point p1, Point p2);
  InputEdge(Point p1, Point p2, std::string left, std::string right);

  EdgeLabel get_primitive_edge(Point p) const;
  void draw() const;
};

std::ostream& operator <<(std::ostream& os, const InputEdge& edge);

#endif //PROCEDURAL_MODELING_INPUT_EDGE_H