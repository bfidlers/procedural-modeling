#include "Input.h"
#include "InputGraph.h"

void load_triangle(InputGraph& g) {
  g.addVertex(0,0);
  g.addVertex(1,0);
  g.addVertex(0,1);

  g.addEdge(0,1);
  g.addEdge(1,2);
  g.addEdge(2,0);
}

void load_square(InputGraph& g) {
  add_square(g,0, 0, 1);
}

void load_square_alt(Graph& g) {
  g.addVertex(1, Point(-0.5, -0.5));
  g.addVertex(2, Point(-0.5, 0.5));
  g.addVertex(3, Point(0.5, 0.5));
  g.addVertex(4, Point(0.5, -0.5));

  g.addEdge(1, 2, "a");
  g.addEdge(2, 3, "b");
  g.addEdge(3, 4, "c");
  g.addEdge(4, 1, "d");
}

void add_square(InputGraph& g, float x, float y, float length, float z) {
  const float base_x = x - length/2;
  const float base_y = y - length/2;
  g.addVertex(base_x, base_y, z);
  g.addVertex(base_x + length, base_y, z);
  g.addVertex(base_x + length, base_y + length, z);
  g.addVertex(base_x ,base_y + length, z);

  const int nb_vertices = g.vertices.size() - 4;

  g.addEdge(nb_vertices,nb_vertices + 1);
  g.addEdge(nb_vertices + 1,nb_vertices + 2);
  g.addEdge(nb_vertices + 2,nb_vertices + 3);
  g.addEdge(nb_vertices + 3,nb_vertices);
}

void load_cube(InputGraph& g) {
  add_square(g,0, 0, 1, -0.5);
  add_square(g,0, 0, 1, 0.5);

  g.addEdge(0, 4);
  g.addEdge(1, 5);
  g.addEdge(2, 6);
  g.addEdge(3, 7);
}

void load_graph(InputGraph& g) {
//  load_triangle(g);
  load_square(g);
//  load_cube(g);
}
