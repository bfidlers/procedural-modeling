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
  g.addVertex(0,0);
  g.addVertex(1,0);
  g.addVertex(1,1);
  g.addVertex(0,1);

  g.addEdge(0,1);
  g.addEdge(1,2);
  g.addEdge(2,3);
  g.addEdge(3,0);
}

void load_graph(InputGraph& g) {
//  load_triangle(g);
  load_square(g);
}
