#include "Graph.h"

#include "Util.h"

void Vertex::unset() {
  hasPosition = false;
}

Edge::Edge(std::string id, std::string inverse, Vertex v1, Vertex v2) {
  this->id = std::move(id);
  this->inverse = std::move(inverse);
  angle = std::round(atan2(v2.pos.y - v1.pos.y, v2.pos.x - v1.pos.x) * 180 / M_PI);
  from = v1.id;
  to = v2.id;
}

void Graph::addVertex(int id) {
  if (vertices.find(id) != vertices.end()) {
    return;
  }
  vertices[id] = Vertex(id);
  adjList[id] = std::vector<Edge>();
}

void Graph::addVertex(int id, Point point) {
  if (vertices.find(id) != vertices.end()) {
    return;
  }
  vertices[id] = Vertex(id, point);
  adjList[id] = std::vector<Edge>();
}

void Graph::addEdge(int from, int to, std::string id) {
  if (vertices.find(from) == vertices.end()) {
    return;
  }
  if (vertices.find(to) == vertices.end()) {
    return;
  }
  std::string inverse = id + "'";
  Edge e1(id, inverse, vertices[from], vertices[to]);
  Edge e2(inverse, id, vertices[to], vertices[from]);
  adjList[from].push_back(e1);
  adjList[to].push_back(e2);
}

void Graph::addEdge(int from, int to, std::string id, int angle) {
  if (vertices.find(from) == vertices.end()) {
    return;
  }
  if (vertices.find(to) == vertices.end()) {
    return;
  }
  std::string inverse = id + "'";
  Edge e1(id, inverse, from, to, angle);
  Edge e2(inverse, id, to, from, inverseAngle(angle));
  adjList[from].push_back(e1);
  adjList[to].push_back(e2);
}

void Graph::unsetVertex(int id) {
  vertices[id].unset();
  markVertexNeighbours(id);
}

void Graph::loosen() {
  if (verticesToLoosen.empty()) {
    std::unordered_set<int> unset;
    findUnsetVertices(unset);

    if (unset.empty()) {
      std::cout << "WARNING: all vertices are set." << std::endl;
      return;
    }

    for (int v: unset) {
      markVertexNeighbours(v);
    }
  }
  if (!vertices[verticesToLoosen.front()].hasPosition) {
    verticesToLoosen.pop();
  }
  unsetVertex(verticesToLoosen.front());
  verticesToLoosen.pop();
}

void Graph::findUnsetVertices(std::unordered_set<int> &unset) {
  for (const auto& pair : vertices) {
    if (!pair.second.hasPosition) {
      unset.insert(pair.second.id);
    }
  }
}

void Graph::getVertexEdges(int vertex, std::vector<Edge> &edges) {
  edges = adjList[vertex];
}

// Marks neighbours of vertex that they are next to be loosened.
void Graph::markVertexNeighbours(int vertex) {
  for (Edge &e: adjList[vertex]) {
    if (e.to != vertex) {
      verticesToLoosen.push(e.to);
    } else {
      verticesToLoosen.push(e.from);
    }
  }
}

std::ostream& operator <<(std::ostream& os, const Edge& e) {
  os << "Edge: " << e.id << ", from: " << e.from << ", to: " << e.to << ", with angle: " << e.angle;
  return os;
}

std::ostream& operator <<(std::ostream& os, const Graph& g) {
  os << "Graph containing the following:" << std::endl;
  for (const auto& pair : g.adjList) {
    const Vertex& v = g.vertices.at(pair.first);
    os << "Vertex " << v.id << ": " << v.pos;
    os << ", with edges: " << std::endl;
    for (const Edge& edge : pair.second) {
      os << edge << std::endl;
    }
    std::cout << std::endl;
  }
  return os;

}
