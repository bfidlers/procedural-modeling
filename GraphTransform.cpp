#include "GraphTransform.h"

#include "Input.h"
#include "GraphIsomorphism.h"
#include "LinearEquationSolver.h"

void testGraphTransform() {
  Rule r;
  load_square_rules1(r);
  std::cout << r << std::endl;

  Graph g;
  load_square_alt(g);
  std::cout << g << std::endl;

  applyRule(r, g);
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

  findGraphDrawing(g);
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
