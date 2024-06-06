#include "LinearEquationSolver.h"
#include <iostream>

#include "Util.h"

void test() {
  testLinearIneq();
  Graph graph;
  loadTestGraph(graph);
  findGraphDrawing(graph);
}

void findGraphDrawing(Graph &graph) {
  int i = 0;
  int max = 10;
  while (true) {
    if (i > max) {
      break;
    }
    std::unordered_map<int, Point> points;
    bool result = solveUnsetVertices(graph, points);
    if (result) {
      std::cout << "Result found" << std::endl;
      setCoordinates(graph, points);
      break;
    }
    std::cout << "No result found" << std::endl;
    graph.loosen();
    i++;
  }
}

void setCoordinates(Graph &graph, std::unordered_map<int, Point> &points) {
  for (auto const& [vertex, point]: points) {
    graph.vertices[vertex].setCoordinates(point);
  }
}

bool solveUnsetVertices(Graph &graph, std::unordered_map<int, Point> &points) {
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

    int start_col_nb = col_nb + 1;

    // glp_set_obj_coef sets the coefficients for the objective function
    // TODO This should probably be randomized.

    glp_add_cols(lp, 4);
    xVariables[vertex] = ++col_nb;
    glp_set_col_bnds(lp, col_nb, GLP_DB, -5.0, 5.0);
    glp_set_obj_coef(lp, col_nb, 1.0);

    yVariables[vertex] = ++col_nb;
    glp_set_col_bnds(lp, col_nb, GLP_DB, -5.0, 5.0);
    glp_set_obj_coef(lp, col_nb, 1.0);

    glp_set_col_bnds(lp, ++col_nb, GLP_LO, 0.1, 0.0);
    glp_set_obj_coef(lp, col_nb, 1.0);

    glp_set_col_bnds(lp, ++col_nb, GLP_LO, 0.1, 0.0);
    glp_set_obj_coef(lp, col_nb, 1.0);

    // If 3D, this should be start_col_nb + 2
    int col_l = start_col_nb + 1;
    for (const Edge& edge: edges){
      col_l++;

      std::cout << edge << std::endl;
      Vertex v = graph.vertices[edge.to];

      if (v.hasPosition) {
        glp_add_rows(lp, 2);
        glp_set_row_bnds(lp, ++row_nb, GLP_FX, v.pos.x, v.pos.x);
        ia[++i] = row_nb, ja[i] = start_col_nb, ar[i] = 1.0;
        ia[++i] = row_nb, ja[i] = col_l, ar[i] = cosine(edge.angle);

        glp_set_row_bnds(lp, ++row_nb, GLP_FX, v.pos.y, v.pos.y);
        ia[++i] = row_nb, ja[i] = start_col_nb+1, ar[i] = 1.0;
        ia[++i] = row_nb, ja[i] = col_l, ar[i] = sine(edge.angle);

        // If xVariable found, that vertex is already processed, and we can use it
        // If not, we can just skip it and it the constraint will be added in the other direction
      } else if(xVariables.find(v.id) != xVariables.end()) {
        glp_add_rows(lp, 2);
        glp_set_row_bnds(lp, ++row_nb, GLP_FX, 0, 0);
        ia[++i] = row_nb, ja[i] = start_col_nb, ar[i] = 1.0;
        ia[++i] = row_nb, ja[i] = xVariables[v.id], ar[i] = -1.0;
        ia[++i] = row_nb, ja[i] = col_l, ar[i] = cosine(edge.angle);

        glp_set_row_bnds(lp, ++row_nb, GLP_FX, 0, 0);
        ia[++i] = row_nb, ja[i] = start_col_nb+1, ar[i] = 1.0;
        ia[++i] = row_nb, ja[i] = yVariables[v.id], ar[i] = -1.0;
        ia[++i] = row_nb, ja[i] = col_l, ar[i] = sine(edge.angle);
      }
    }
  }

  glp_load_matrix(lp, i, ia, ja, ar);

  glp_simplex(lp, NULL);

  for (int vertex : unsetVertices) {
    double x = glp_get_col_prim(lp, xVariables[vertex]);
    double y = glp_get_col_prim(lp, yVariables[vertex]);
    points[vertex] = Point(x, y);
    std::cout << "Solution vertex: " << vertex << ": x = " << x << ", y = " << y << std::endl;
  }

  int result = glp_get_status(lp);

  // Clean up
  glp_delete_prob(lp);
  glp_free_env();

  if (result == GLP_NOFEAS || result == GLP_INFEAS) {
    return false;
  }

  return true;
}

void loadTestGraph(Graph &graph) {
  graph.addVertex(1, Point(0, 0));
  graph.addVertex(2, Point(0, 1));
  graph.addVertex(3, Point(1, 1));
  graph.addVertex(4, Point(1, 0));
  graph.addVertex(5);
  graph.addVertex(6);

  graph.addEdge(1, 2, "a");
  graph.addEdge(2, 3, "b");
  graph.addEdge(4, 1, "d");

//  graph.addEdge(3, 4, "c");
  graph.addEdge(3, 5, "e", -90);
  graph.addEdge(5, 6, "f", 0);
  graph.addEdge(6, 4, "g", -90);

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
