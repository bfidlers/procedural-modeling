#ifndef PROCEDURAL_MODELING_GRAPH_H
#define PROCEDURAL_MODELING_GRAPH_H

#include "Vertex.h"
#include "Edge.h"
#include "Primitive.h"

#include <iostream>
#include <vector>

class Graph {
public:
  std::vector<Vertex> vertices;
  std::vector<Edge> edges;

  Graph() = default;

  void add(Vertex &vertex);
  void add(Edge &edge);

  void split_primitives(std::vector<Primitive>& primitives);
  void draw() const;
};

std::ostream& operator <<(std::ostream& os, const Graph& g);

#endif //PROCEDURAL_MODELING_GRAPH_H
