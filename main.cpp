#include "Input.h"
#include "Graph.h"
#include "Primitive.h"

#include <iostream>
#include <vector>

int main() {
  Graph g;
  load_graph(g);

  // Split graph into primitives
  std::vector<Primitive> primitives;
  g.split_primitives(primitives);
  for (const Primitive& p: primitives) {
    std::cout << p << std::endl;
  }
}
