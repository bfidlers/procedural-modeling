#ifndef PROCEDURAL_MODELING_GRAPH_TRANSFORM_H
#define PROCEDURAL_MODELING_GRAPH_TRANSFORM_H

#include "Rule.h"

void testGraphTransform();
bool applyRule(Rule &r, Graph &g);
void deleteTransform(Rule &r, Graph &g, std::unordered_map<int, int> &mapping);

#endif //PROCEDURAL_MODELING_GRAPH_TRANSFORM_H
