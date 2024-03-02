#ifndef PROCEDURAL_MODELING_GRAPH_H
#define PROCEDURAL_MODELING_GRAPH_H

#include "Vertex.h"
#include "Primitive.h"

#include <iostream>
#include <vector>

class Graph {
public:
  std::vector<Vertex> vertices;

  Graph() = default;

  void add(Vertex &vertex);

  void split_primitives(std::vector<Primitive>& primitives);
};

std::ostream& operator <<(std::ostream& os, const Graph& g);

#endif //PROCEDURAL_MODELING_GRAPH_H
