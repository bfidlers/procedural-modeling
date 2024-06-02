#ifndef PROCEDURAL_MODELING_GRAPH_H
#define PROCEDURAL_MODELING_GRAPH_H

#include <iostream>
#include <unordered_map>
#include <vector>

#include "Point.h"

class Vertex {
public:
  int id;
  bool hasPosition = false;
  Point pos;

  Vertex() {}
  Vertex(int id) : id(id)  {}
  Vertex(int id, Point pos) : id(id) , pos(pos) {}
};

class Edge {
public:
  int from;
  int to;
  float angle;
  Edge(int from, int to, float angle) : from(from), to(to), angle(angle) {}
  Edge(Vertex v1, Vertex v2);
};

std::ostream& operator <<(std::ostream& os, const Edge& e);

class Graph {
  public:
  std::unordered_map<int, Vertex> vertices;
  std::unordered_map<int, std::vector<Edge>> adjList;

  Graph() = default;

  void addVertex(int id, Point point);
  void addEdge(int from, int to);
};

std::ostream& operator <<(std::ostream& os, const Graph& g);

#endif //PROCEDURAL_MODELING_GRAPH_H
