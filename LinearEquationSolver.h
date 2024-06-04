#ifndef PROCEDURAL_MODELING_LINEAR_EQUATION_SOLVER_H
#define PROCEDURAL_MODELING_LINEAR_EQUATION_SOLVER_H

#include <glpk.h>

#include "Graph.h"

void test();
void findGraphDrawing(Graph &graph);
bool solveUnsetVertices(Graph &graph);
void loadTestGraph(Graph &g);
void testLinearIneq();

#endif //PROCEDURAL_MODELING_LINEAR_EQUATION_SOLVER_H
