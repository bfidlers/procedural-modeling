#include "Rule.h"

std::ostream& operator <<(std::ostream& os, const Rule& r) {
  os << "Rule: " << r.lhs.shorthand() << " to: " << r.rhs.shorthand() << std::endl;
  os << "with connections: ";
  for (auto const& [i1, i2]: r.connections) {
    std::cout << i1 << " -> " << i2 << ", ";
  }
  os << std::endl;
  return os;
}
