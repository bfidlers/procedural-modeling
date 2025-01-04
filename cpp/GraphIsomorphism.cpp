#include "GraphIsomorphism.h"
#include "Input.h"

void testIsomorphism() {
  testSimpleExample();
  testFullIsomorphism();
  testFalseIsomorphism();
}

void testSimpleExample() {
  std::cout << "Testing simple isomorphism:" << std::endl;

  Graph g1;
  Graph g2;

  g1.addVertex(5, Point(0, 0));
  g1.addVertex(6, Point(0, 1));

  g1.addEdge(5, 6, "a");

  std::cout << "graph 1:" << std::endl;
  std::cout << g1 << std::endl;

  load_square_alt(g2);

  std::cout << "graph 2:" << std::endl;
  std::cout << g2 << std::endl;

  std::unordered_map<int, int> mapping;
  isSubgraphIsomorphic(g1, g2, mapping);
}

void testFullIsomorphism() {
  std::cout << "Testing full isomorphism:" << std::endl;

  Graph g1;
  Graph g2;

  g1.addVertex(5, Point(0, 0));
  g1.addVertex(6, Point(0, 1));
  g1.addVertex(7, Point(1, 1));
  g1.addVertex(8, Point(1, 0));

  g1.addEdge(5, 6, "a");
  g1.addEdge(6, 7, "b");
  g1.addEdge(8, 7, "a");
  g1.addEdge(5, 8, "b");

  std::cout << "graph 1:" << std::endl;
  std::cout << g1 << std::endl;

  load_square_alt(g2);

  std::cout << "graph 2:" << std::endl;
  std::cout << g2 << std::endl;

  std::unordered_map<int, int> mapping;
  isSubgraphIsomorphic(g1, g2, mapping);
}

void testFalseIsomorphism() {
  std::cout << "Testing false isomorphism:" << std::endl;

  Graph g1;
  Graph g2;

  g1.addVertex(5, Point(0, 0));
  g1.addVertex(6, Point(0, 1));
  g1.addVertex(7, Point(2, 1));

  g1.addEdge(5, 6, "a");
  g1.addEdge(6, 7, "e");

  std::cout << "graph 1:" << std::endl;
  std::cout << g1 << std::endl;

  load_square_alt(g2);

  std::cout << "graph 2:" << std::endl;
  std::cout << g2 << std::endl;

  std::unordered_map<int, int> mapping;
  isSubgraphIsomorphic(g1, g2, mapping);
}

bool isSubgraphIsomorphic(Graph &g1, Graph &g2, std::unordered_map<int, int> &mapping) {
  if (g1.vertexSize() == 0) {
    return true;
  }
  if (g1.vertexSize() > g2.vertexSize()) {
    std::cout << "WARNING: First graph has more vertices than the second." << std::endl;
    return false;
  }
  if (g1.edgeSize() > g2.edgeSize()) {
    std::cout << "WARNING: First graph has more edges than the second." << std::endl;
    return false;
  }

  auto it = g1.vertices.begin();
  std::unordered_map<int, int> nextPoints;
  bool firstMatch = findFirstMatch(it->first, g1, g2, mapping, nextPoints);

  if (!firstMatch) {
    std::cout << "WARNING: Could not find any vertex that matches: " << it->second << std::endl;
    return false;
  }

  bool result = findNextMatches(g1, g2, mapping, nextPoints);
  if (!result) {
    return false;
  }

  if (mapping.size() != g1.vertexSize()) {
    std::cout << "WARNING: Graph is disjoint, as of now this is not supported yet. " << std::endl;
    // TODO repeat algorithm for vertices not yet in the mapping.
  }

  std::cout << "Successful mapping found." << std::endl;
  for (auto const& [i1, i2]: mapping) {
    std::cout << i1 << " -> " << i2 << std::endl;
  }

  return true;
}

bool findFirstMatch(int vertex, Graph &g1, Graph &g2,
                    std::unordered_map<int, int> &mapping,
                    std::unordered_map<int, int> &nextPoints) {
  std::vector<Edge> &edges1 = g1.adjList[vertex];

  // TODO randomize entry here:
  //  start in a random place by shuffling the indices in a different vector and then, iterate based on this vector
  for (auto const& [i2, v2]: g2.vertices) {
    std::vector<Edge> &edges2 = g2.adjList[i2];
    bool result = matchEdges(edges1, edges2, nextPoints);
    if (result) {
      std::cout << "First match: " << vertex << " -> " << i2 << std::endl;
      mapping[vertex] = i2;
      return true;
    }
  }
  return false;
}

bool findNextMatches(Graph &g1, Graph &g2,
                    std::unordered_map<int, int> &mapping,
                    std::unordered_map<int, int> &currentVertices) {

  for (auto const& [i1, i2]: currentVertices) {
    if (mapping.contains(i1)) {
      continue;
    }

    std::vector<Edge> &edges1 = g1.adjList[i1];
    std::vector<Edge> &edges2 = g2.adjList[i2];
    std::unordered_map<int, int> nextPoints;
    bool edgesMatch = matchEdges(edges1, edges2, nextPoints);
    if (edgesMatch) {
      std::cout << "Next match: " << i1 << " -> " << i2 << std::endl;
      mapping[i1] = i2;
      bool result = findNextMatches(g1, g2, mapping, nextPoints);
      if (!result) {
        std::cout << "WARNING: : Problem while trying to follow edges of: " << g1.vertices[i1] << std::endl;
        return false;
      }
    } else {
      std::cout << "WARNING: Vertex: " << g1.vertices[i1] << ", did not match, vertex: " << g2.vertices[i2] << std::endl;
      return false;
    }
  }
  return true;
}

bool matchEdges(std::vector<Edge> &edges1,
                std::vector<Edge> &edges2,
                std::unordered_map<int, int> &possibleMapping) {
  if (edges1.size() > edges2.size()) {
    return false;
  }
  for (const Edge& e1: edges1) {
    int match = findMatchingEdge(e1, edges2);
    if (match == -1) {
      return false;
    }
    possibleMapping[e1.to] = match;
  }
  return true;
}

int findMatchingEdge(const Edge &e1, std::vector<Edge> &edges) {
  for (const Edge& e: edges) {
    if (e == e1) {
      return e.to;
    }
  }
  return -1;
}
