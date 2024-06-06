#ifndef PROCEDURAL_MODELING_GRAPH_ISOMORPHISM_H
#define PROCEDURAL_MODELING_GRAPH_ISOMORPHISM_H

#include "Graph.h"

#include <vector>

void testIsomorphism();
void testSimpleExample();
void testFullIsomorphism();
void testFalseIsomorphism();

bool isSubgraphIsomorphic(Graph &g1, Graph &g2, std::unordered_map<int, int> &mapping);

bool findFirstMatch(int vertex, Graph &g1, Graph &g2, std::unordered_map<int, int> &mapping, std::unordered_map<int, int> &nextPoints);
bool findNextMatches(Graph &g1, Graph &g2, std::unordered_map<int, int> &mapping, std::unordered_map<int, int> &currentVertices);
bool matchEdges(std::vector<Edge> &edges1, std::vector<Edge> &edges2, std::unordered_map<int, int> &possibleMapping);
int findMatchingEdge(const Edge &e1, std::vector<Edge> &edges);

#endif //PROCEDURAL_MODELING_GRAPH_ISOMORPHISM_H
