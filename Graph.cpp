#include "Graph.h"

void Graph::addVertex(float x, float y) {
  Vertex vertex(x, y);
  vertices.push_back(vertex);
}

void Graph::addEdge(int v1, int v2) {
  Edge edge(vertices[v1].pos, vertices[v2].pos);
  vertices[v1].add(edge);
  vertices[v2].add(edge);
  edges.push_back(edge);
}

void Graph::addEdge(int v1, int v2, std::string left, std::string right) {
  Edge edge(vertices[v1].pos, vertices[v2].pos, left, right);
  vertices[v1].add(edge);
  vertices[v2].add(edge);
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
