#include "Rule.h"

void Rule::init(Graph &new_lhs, Graph &new_rhs, std::unordered_map<int, int> &new_connections) {
  lhs = new_lhs;
  rhs = new_rhs;
  connections = new_connections;
}

void load_square_rules1(Rule &r) {
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

  r.init(lhs, rhs, mapping);
}

std::ostream& operator <<(std::ostream& os, const Rule& r) {
  os << "Rule: " << r.lhs.shorthand() << " to: " << r.rhs.shorthand() << std::endl;
  os << "with connections: ";
  for (auto const& [i1, i2]: r.connections) {
    std::cout << i1 << " -> " << i2 << ", ";
  }
  os << std::endl;
  return os;
}
