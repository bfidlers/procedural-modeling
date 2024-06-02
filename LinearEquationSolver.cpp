#include "LinearEquationSolver.h"
#include <iostream>
#include <glpk.h>

#include "Graph.h"

void loadTestGraph() {
  Graph graph;
  graph.addVertex(1, Point(0, 0));
  graph.addVertex(2, Point(0, 1));
  graph.addVertex(3, Point(1, 1));
  graph.addVertex(4, Point(1, 0));

  graph.addEdge(1, 2, "a");
  graph.addEdge(2, 3, "b");
  graph.addEdge(3, 4, "c");
  graph.addEdge(4, 1, "d");

  std::cout << "Test graph:" << std::endl;
  std::cout << graph << std::endl;
}

void testLinearIneq() {
  // Create a problem object
  glp_prob *lp;
  lp = glp_create_prob();
  glp_set_prob_name(lp, "linear_inequality");

  // Define the direction of the optimization
  glp_set_obj_dir(lp, GLP_MAX); // or GLP_MIN for minimization

  // Define the number of variables (columns)
  glp_add_cols(lp, 2);
  glp_set_col_name(lp, 1, "x1");
  glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0); // x1 >= 0
  glp_set_col_name(lp, 2, "x2");
  glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0); // x2 >= 0

  // Set the coefficients for the objective function
  glp_set_obj_coef(lp, 1, 1.0); // Coefficient for x1
  glp_set_obj_coef(lp, 2, 1.0); // Coefficient for x2

  // Define the number of constraints (rows)
  glp_add_rows(lp, 2);
  glp_set_row_name(lp, 1, "c1");
  glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 4.0); // x1 + 2x2 <= 4
  glp_set_row_name(lp, 2, "c2");
  glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 3.0); // 2x1 + x2 <= 3

  // Define the constraint matrix
  int ia[1+4], ja[1+4];
  double ar[1+4];
  ia[1] = 1, ja[1] = 1, ar[1] = 1.0; // a[1,1] = 1
  ia[2] = 1, ja[2] = 2, ar[2] = 2.0; // a[1,2] = 2
  ia[3] = 2, ja[3] = 1, ar[3] = 2.0; // a[2,1] = 2
  ia[4] = 2, ja[4] = 2, ar[4] = 1.0; // a[2,2] = 1

  // Load the matrix
  glp_load_matrix(lp, 4, ia, ja, ar);

  // Solve the problem using the simplex method
  glp_simplex(lp, NULL);

  // Retrieve and print the solution
  double x1 = glp_get_col_prim(lp, 1);
  double x2 = glp_get_col_prim(lp, 2);
  std::cout << "Solution: x1 = " << x1 << ", x2 = " << x2 << std::endl;

  // Clean up
  glp_delete_prob(lp);
  glp_free_env();
}
