#ifndef PROCEDURAL_MODELING_GRAPH_H
#define PROCEDURAL_MODELING_GRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <string>

#include "Point.h"

class Vertex {
public:
  int id;
  bool hasPosition = false;
  Point pos;

  Vertex() {}
  Vertex(int id) : id(id)  {}
  Vertex(int id, Point pos) : id(id) , pos(pos), hasPosition(true) {}

  void unset();
  void setCoordinates(Point pos);
};

std::ostream& operator <<(std::ostream& os, const Vertex& v);

class Edge {
public:
  std::string id;
  std::string inverse;
  int from;
  int to;
  int angle;

  Edge(std::string id, std::string inverse, int from, int to, int angle) : id(id), inverse(inverse), from(from), to(to), angle(angle) {}
  Edge(std::string id, std::string inverse, Vertex v1, Vertex v2);

  bool isInverse() const;
};

std::ostream& operator <<(std::ostream& os, const Edge& e);
bool operator==(Edge const& e1, Edge const& e2);

class Graph {
  public:
  std::queue<int> verticesToLoosen;
  std::unordered_map<int, Vertex> vertices;
  std::unordered_map<int, std::vector<Edge>> adjList;

  Graph() = default;

  int vertexSize() const;
  int edgeSize() const;

  void addVertex(int id);
  void addVertex(int id, Point point);
  void addEdge(int from, int to, std::string id);
  void addEdge(int from, int to, std::string id, int angle);
  void addSingleEdge(int from, int to, std::string id, int angle);

  void removeVertex(int id);
  void removeSingleEdge(int from, int to);
  void removeEdge(int from, int to);

  void unsetVertex(int id);
  void loosen();
  void findUnsetVertices(std::unordered_set<int> &unset);
  void getVertexEdges(int vertex, std::vector<Edge> &edges);
  void getVertexEdgesIds(int vertex, std::vector<std::string> &edges);
  void markVertexNeighbours(int vertex);

  std::string shorthand() const;

  void draw();
};

std::ostream& operator <<(std::ostream& os, const Graph& g);

#endif //PROCEDURAL_MODELING_GRAPH_H
