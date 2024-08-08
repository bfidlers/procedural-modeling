#ifndef PROCEDURAL_MODELING_RULE_H
#define PROCEDURAL_MODELING_RULE_H

#include "Graph.h"

class Rule {
public:
  Graph lhs;
  Graph rhs;
  std::unordered_map<int, int> connections;

  Rule() = default;
  Rule(Graph &lhs, Graph &rhs, std::unordered_map<int, int> &connections) : lhs(lhs), rhs(rhs), connections(connections) {}
  void init(Graph &lhs, Graph &rhs, std::unordered_map<int, int> &connections);
};

void load_square_rules(std::vector<Rule> &rules);
void load_square_rule1(Rule &r);
void load_square_rule2(Rule &r);
void load_square_rule3(Rule &r);
void load_square_rule4(Rule &r);
void load_square_rule5(Rule &r);

std::ostream& operator <<(std::ostream& os, const Rule& r);

#endif //PROCEDURAL_MODELING_RULE_H
