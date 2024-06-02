#include "LinearEquationSolver.h"
#include <iostream>

#include "Util.h"

void test() {
  testLinearIneq();
  Graph graph;
  loadTestGraph(graph);
  graph.unsetVertex(2);
  graph.unsetVertex(4);
  solveUnsetVertices(graph);
}

void solveUnsetVertices(Graph &graph) {
  std::unordered_set<int> unsetVertices;
  graph.findUnsetVertices(unsetVertices);

  std::unordered_map<int, int> xVariables;
  std::unordered_map<int, int> yVariables;

  glp_prob *lp;
  lp = glp_create_prob();
  glp_set_prob_name(lp, "test");

  glp_set_obj_dir(lp, GLP_MAX);

  // Each unset Vertex has and row for each coordinate, most likely it has two edges, to be safe we multiply this by two.
  // TODO Should be updated later.
  int nb_rows = 1 + unsetVertices.size() * 2 * 2 * 2;
  int ia[nb_rows], ja[nb_rows];
  double ar[nb_rows];

  int col_nb = 0;
  int row_nb = 0;
  int i = 0;

  for (int vertex : unsetVertices) {
    std::vector<Edge> edges;
    graph.getVertexEdges(vertex, edges);
    for (const Edge& edge: edges){
      std::cout << edge << std::endl;
    }

    int start_col_nb = col_nb + 1;
    int start_row_nb = row_nb + 1;

    // glp_set_obj_coef sets the coefficients for the objective function
    // TODO This should probably be randomized.

    glp_add_cols(lp, 4);
    xVariables[vertex] = ++col_nb;
    glp_set_col_bnds(lp, col_nb, GLP_LO, 0.0, 0.0);
    glp_set_obj_coef(lp, col_nb, 1.0);

    yVariables[vertex] = ++col_nb;
    glp_set_col_bnds(lp, col_nb, GLP_LO, 0.0, 0.0);
    glp_set_obj_coef(lp, col_nb, 1.0);

    glp_set_col_bnds(lp, ++col_nb, GLP_FR, 0.0, 0.0);
    glp_set_obj_coef(lp, col_nb, 1.0);

    glp_set_col_bnds(lp, ++col_nb, GLP_FR, 0.0, 0.0);
    glp_set_obj_coef(lp, col_nb, 1.0);

    // TODO should probably also be a for loop.
    glp_add_rows(lp, 4);
    Vertex v1 = graph.vertices[edges[0].to];
    glp_set_row_bnds(lp, ++row_nb, GLP_FX, v1.pos.x, v1.pos.x);
    glp_set_row_bnds(lp, ++row_nb, GLP_FX, v1.pos.y, v1.pos.y);
    Vertex v2 = graph.vertices[edges[1].to];
    glp_set_row_bnds(lp, ++row_nb, GLP_FX, v2.pos.x, v2.pos.x);
    glp_set_row_bnds(lp, ++row_nb, GLP_FX, v2.pos.y, v2.pos.y);

    // TODO check if the minus can't be removed, and then hopefully the constraint that l can be less then 0 can be removed.
    ia[++i] = start_row_nb, ja[i] = start_col_nb, ar[i] = 1.0;
    ia[++i] = start_row_nb, ja[i] = start_col_nb+2, ar[i] = -cosine(edges[0].angle);
    ia[++i] = start_row_nb+1, ja[i] = start_col_nb+1, ar[i] = 1.0;
    ia[++i] = start_row_nb+1, ja[i] = start_col_nb+2, ar[i] = -sine(edges[0].angle);
    ia[++i] = start_row_nb+2, ja[i] = start_col_nb, ar[i] = 1.0;
    ia[++i] = start_row_nb+2, ja[i] = start_col_nb+3, ar[i] = -cosine(edges[1].angle);
    ia[++i] = start_row_nb+3, ja[i] = start_col_nb+1, ar[i] = 1.0;
    ia[++i] = start_row_nb+3, ja[i] = start_col_nb+3, ar[i] = -sine(edges[1].angle);
  }

  glp_load_matrix(lp, i, ia, ja, ar);

  glp_simplex(lp, NULL);

  for (int vertex : unsetVertices) {
    double x = glp_get_col_prim(lp, xVariables[vertex]);
    double y = glp_get_col_prim(lp, yVariables[vertex]);
    std::cout << "Solution vertex: " << vertex << ": x = " << x << ", y = " << y << std::endl;
  }

  // Clean up
  glp_delete_prob(lp);
  glp_free_env();
}

void loadTestGraph(Graph &graph) {
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
