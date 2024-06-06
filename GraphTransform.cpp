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

  std::cout << g << std::endl;
}

bool applyRule(Rule &r, Graph &g) {
  std::unordered_map<int, int> mapping;
  bool isoMorphic = isSubgraphIsomorphic(r.lhs, g, mapping);
  if (!isoMorphic) {
    std::cout << "WARNING: rule does not seem to be applicable." << std::endl;
    return false;
  }

  deleteTransform(r, g, mapping);

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
