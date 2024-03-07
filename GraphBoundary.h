#ifndef PROCEDURAL_MODELING_GRAPH_BOUNDARY_H
#define PROCEDURAL_MODELING_GRAPH_BOUNDARY_H

#include <iostream>

class GraphBoundary {
public:
  std::string graph_boundary;

  GraphBoundary(std::string boundary);
};

std::ostream& operator <<(std::ostream& os, const GraphBoundary& p);

#endif //PROCEDURAL_MODELING_GRAPH_BOUNDARY_H
