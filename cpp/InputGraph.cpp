#include "InputGraph.h"

void InputGraph::addVertex(float x, float y, float z) {
  InputVertex vertex(x, y, z);
  vertices.push_back(vertex);
}

void InputGraph::addEdge(int v1, int v2) {
  InputEdge edge(vertices[v1].pos, vertices[v2].pos);
  vertices[v1].add(edge);
  vertices[v2].add(edge);
  edges.push_back(edge);
}

void InputGraph::addEdge(int v1, int v2, std::string left, std::string right) {
  InputEdge edge(vertices[v1].pos, vertices[v2].pos, left, right);
  vertices[v1].add(edge);
  vertices[v2].add(edge);
  edges.push_back(edge);
}

void InputGraph::split_primitives(std::vector<Primitive>& primitives) {
  for (const InputVertex& v: vertices) {
    primitives.push_back(v.generate_primitive());
  }
}

void InputGraph::draw() const {
  for (const InputEdge &e: edges) {
    e.draw();
  }
}

std::ostream& operator <<(std::ostream& os, const InputGraph& g) {
  os << "Graph containing the following:" << std::endl;
  os << "Vertices:" << std::endl;
  for (const InputVertex& v: g.vertices) {
    os << v << std::endl;
  }
  return os;
}
