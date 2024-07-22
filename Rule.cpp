#include "Rule.h"

void Rule::init(Graph &new_lhs, Graph &new_rhs, std::unordered_map<int, int> &new_connections) {
  lhs = new_lhs;
  rhs = new_rhs;
  connections = new_connections;
}

void load_square_rules(std::vector<Rule> &rules) {
  // If direction inverse, some issues...
  Rule r1;
  load_square_rule1(r1);
  rules.push_back(r1);
  Rule r2;
  load_square_rule2(r2);
  rules.push_back(r2);
  Rule r3;
  load_square_rule3(r3);
  rules.push_back(r3);
  Rule r4;
  load_square_rule4(r4);
  rules.push_back(r4);
//  Rule r5;
//  load_square_rule5(r5);
//  rules.push_back(r5);
}

void load_square_rule1(Rule &r) {
  Graph lhs;
  lhs.addVertex(0);
  lhs.addVertex(1);
  lhs.addEdge(0, 1, "b", 0);

  Graph rhs;
  rhs.addVertex(0);
  rhs.addVertex(1);
  rhs.addVertex(2);
  rhs.addVertex(3);
  rhs.addEdge(0, 1, "a", 90);
  rhs.addEdge(2, 1, "b", 0);
  rhs.addEdge(2, 3, "a", 90);

  std::unordered_map<int, int> mapping;
  mapping[0] = 0;
  mapping[1] = 3;

  r.init(lhs, rhs, mapping);
}

void load_square_rule2(Rule &r) {
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

void load_square_rule3(Rule &r) {
  Graph lhs;
  lhs.addVertex(0);
  lhs.addVertex(1);
  lhs.addEdge(0, 1, "b", 0);

  Graph rhs;
  rhs.addVertex(0);
  rhs.addVertex(1);
  rhs.addVertex(2);
  rhs.addVertex(3);
  rhs.addEdge(0, 1, "b", 0);
  rhs.addEdge(1, 2, "a", 90);
  rhs.addEdge(2, 3, "b", 0);

  std::unordered_map<int, int> mapping;
  mapping[0] = 0;
  mapping[1] = 3;

  r.init(lhs, rhs, mapping);
}

void load_square_rule4(Rule &r) {
  Graph lhs;
  lhs.addVertex(0);
  lhs.addVertex(1);
  lhs.addEdge(0, 1, "b", 0);

  Graph rhs;
  rhs.addVertex(0);
  rhs.addVertex(1);
  rhs.addVertex(2);
  rhs.addVertex(3);
  rhs.addEdge(0, 1, "b", 0);
  rhs.addEdge(2, 1, "a", 90);
  rhs.addEdge(2, 3, "b", 0);

  std::unordered_map<int, int> mapping;
  mapping[0] = 0;
  mapping[1] = 3;

  r.init(lhs, rhs, mapping);
}

void load_square_rule5(Rule &r) {
  Graph lhs;

  Graph rhs;
  rhs.addVertex(1);
  rhs.addVertex(2);
  rhs.addVertex(3);
  rhs.addVertex(4);

  rhs.addEdge(1, 2, "a", 90);
  rhs.addEdge(2, 3, "b", 0);
  rhs.addEdge(4, 3, "a", 90);
  rhs.addEdge(1, 4, "b", 0);

  std::unordered_map<int, int> mapping;

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
