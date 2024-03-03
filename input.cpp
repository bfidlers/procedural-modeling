#include "input.h"
#include "Edge.h"
#include "Primitive.h"
#include "Vertex.h"
#include "Graph.h"

#include <iostream>
#include <vector>

void load_graph(Graph& g) {
  Vertex v1(0,0);
  Vertex v2(1,0);
  Vertex v3(1,1);
  Vertex v4(0,1);

  Edge e1(v1.pos, v2.pos);
  Edge e2(v2.pos, v3.pos);
  Edge e3(v3.pos, v4.pos);
  Edge e4(v4.pos, v1.pos);

  v1.add(e1);
  v1.add(e4);
  v2.add(e1);
  v2.add(e2);
  v3.add(e2);
  v3.add(e3);
  v4.add(e3);
  v4.add(e4);

  g.add(v1);
  g.add(v2);
  g.add(v3);
  g.add(v4);

}