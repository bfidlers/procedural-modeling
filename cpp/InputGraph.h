#ifndef PROCEDURAL_MODELING_INPUT_GRAPH_H
#define PROCEDURAL_MODELING_INPUT_GRAPH_H

#include "InputVertex.h"
#include "InputEdge.h"
#include "Primitive.h"

#include <iostream>
#include <vector>

class InputGraph {
public:
  std::vector<InputVertex> vertices;
  std::vector<InputEdge> edges;

  InputGraph() = default;

  void addVertex(float x, float y, float z = 0);
  void addEdge(int v1, int v2);
  void addEdge(int v1, int v2, std::string left, std::string right);

  void split_primitives(std::vector<Primitive>& primitives);
  void draw() const;
};

std::ostream& operator <<(std::ostream& os, const InputGraph& g);

#endif //PROCEDURAL_MODELING_INPUT_GRAPH_H
