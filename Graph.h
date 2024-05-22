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

  void addVertex(float x, float y);
  void addEdge(int v1, int v2);
  void addEdge(int v1, int v2, std::string left, std::string right);

  void split_primitives(std::vector<Primitive>& primitives);
  void draw() const;
};

std::ostream& operator <<(std::ostream& os, const Graph& g);

#endif //PROCEDURAL_MODELING_GRAPH_H
