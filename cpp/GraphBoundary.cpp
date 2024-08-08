#include "GraphBoundary.h"

GraphBoundary::GraphBoundary(std::string boundary) {
  graph_boundary = boundary;
}

std::ostream& operator <<(std::ostream& os, const GraphBoundary& boundary) {
  os << boundary.graph_boundary << std::endl;
  return os;
}
