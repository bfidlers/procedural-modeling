#include "GraphTransform.h"

void testGraphTransform() {
  Graph lhs;
  lhs.addVertex(0);
  lhs.addVertex(1);
  lhs.addEdge(0, 1, "a", -90);

  Graph rhs;
  rhs.addVertex(0);
  rhs.addVertex(1);
  rhs.addVertex(2);
  rhs.addVertex(3);
  rhs.addEdge(0, 1, "a", -90);
  rhs.addEdge(1, 2, "b", 0);
  rhs.addEdge(2, 3, "c", -90);

  std::unordered_map<int, int> mapping;
  mapping[0] = 0;
  mapping[1] = 3;
  Rule r = Rule(lhs, rhs, mapping);
  std::cout << r << std::endl;
}
