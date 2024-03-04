#include "Graph.h"

void Graph::add(Vertex &vertex) {
  vertices.push_back(vertex);
}

void Graph::add(Edge &edge) {
  edges.push_back(edge);
}

void Graph::split_primitives(std::vector<Primitive>& primitives) {
  for (const Vertex& v: vertices) {
    primitives.push_back(v.generate_primitive());
  }
}

void Graph::draw() const {
  for (const Edge &e: edges) {
    e.draw();
  }
}

std::ostream& operator <<(std::ostream& os, const Graph& g) {
  os << "Graph containing the following:" << std::endl;
  os << "Vertices:" << std::endl;
  for (const Vertex& v: g.vertices) {
    os << v << std::endl;
  }
  return os;
}
