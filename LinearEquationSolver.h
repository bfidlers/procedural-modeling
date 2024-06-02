#ifndef PROCEDURAL_MODELING_LINEAR_EQUATION_SOLVER_H
#define PROCEDURAL_MODELING_LINEAR_EQUATION_SOLVER_H

#include <glpk.h>

#include "Graph.h"

void test();
void solveUnsetVertices(Graph &graph);
void loadTestGraph(Graph &g);
void testLinearIneq();

#endif //PROCEDURAL_MODELING_LINEAR_EQUATION_SOLVER_H
