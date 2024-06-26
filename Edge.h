#ifndef PROCEDURAL_MODELING_EDGE_H
#define PROCEDURAL_MODELING_EDGE_H

#include "Point.h"
#include "EdgeLabel.h"

#include <iostream>
#include <string>

class Edge {
public:
  EdgeLabel label = EdgeLabel(0);
  Point origin;
  Point dest;

  Edge(EdgeLabel label);
  Edge(int angle);
  Edge(int angle, std::string left, std::string right);
  Edge(Point p1, Point p2);
  Edge(Point p1, Point p2, std::string left, std::string right);

  EdgeLabel get_primitive_edge(Point p) const;
  void draw() const;
};

std::ostream& operator <<(std::ostream& os, const Edge& edge);

#endif //PROCEDURAL_MODELING_EDGE_H