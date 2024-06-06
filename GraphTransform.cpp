#include "GraphTransform.h"

#include "Input.h"
#include "GraphIsomorphism.h"

void testGraphTransform() {
  Graph lhs;
  lhs.addVertex(0);
  lhs.addVertex(1);
  lhs.addEdge(0, 1, "a", 90);

  Graph rhs;
  rhs.addVertex(0);
  rhs.addVertex(1);
  rhs.addVertex(2);
  rhs.addVertex(3);
  rhs.addEdge(0, 1, "a", 90);
  rhs.addEdge(1, 2, "b", 0);
  rhs.addEdge(2, 3, "a", 90);

  std::unordered_map<int, int> mapping;
  mapping[0] = 0;
  mapping[1] = 3;

  Rule r = Rule(lhs, rhs, mapping);
  std::cout << r << std::endl;

  Graph g;
  load_square_alt(g);
  std::cout << g << std::endl;

  bool result = applyRule(r, g);

}

bool applyRule(Rule &r, Graph &g) {
  std::unordered_map<int, int> mapping;
  bool isoMorphic = isSubgraphIsomorphic(r.lhs, g, mapping);
  if (!isoMorphic) {
    std::cout << "WARNING: rule does not seem to be applicable." << std::endl;
    return false;
  }

  deleteTransform(r, g, mapping);
  std::cout << g << std::endl;

  additionTransform(r, g, mapping);
  std::cout << g << std::endl;

  return true;
}

void deleteTransform(Rule &r, Graph &g, std::unordered_map<int, int> &mapping) {
  for (auto const& [i1, i2]: mapping) {
    if (r.connections.contains(i1)) {
      std::vector<std::string> edgeIds;
      r.lhs.getVertexEdgesIds(i1, edgeIds);
      std::vector<Edge> &correspondingEdges = g.adjList[mapping.at(i1)];
      for (const std::string &s: edgeIds) {
        for (const Edge &e: correspondingEdges) {
          if (s == e.id) {
            std::cout << "INFO: removing edge: " << e << std::endl;
            g.removeEdge(e.from, e.to);
          }
        }
      }
    } else {
      std::cout << "INFO: removing vertex: " << i2 << std::endl;
      g.removeVertex(i2);
    }
  }
}

void additionTransform(Rule &r, Graph &g, std::unordered_map<int, int> &mapping) {
  // This is a map from rhs vertex ids to ids in the graph
  std::unordered_map<int, int> newIds;

  // First add mapping for connection points.
  for (auto const& [left, right]: r.connections) {
    newIds[right] = mapping.at(left);
  }
  // Generate new ids.
  for (auto const& [i, v]: r.rhs.vertices) {
    if (!newIds.contains(i)) {
      newIds[i] = rand();
    }
  }

  // Add new vertices
  for (auto const& [i, v]: r.rhs.vertices) {
    // Some vertices are already in the graph, but if you add vertices with the same id,
    // they are just skipped.
    std::cout << "INFO: adding vertex: " << newIds.at(i) << std::endl;
    g.addVertex(newIds.at(i));
  }

  // Add new edges
  for (auto const& [i, v]: r.rhs.vertices) {
    for (const Edge &e: r.rhs.adjList[i]) {
      std::cout << "INFO: adding new edge: " << e << std::endl;
      g.addSingleEdge(newIds.at(e.from), newIds.at(e.to), e.id, e.angle);
    }
  }
}
