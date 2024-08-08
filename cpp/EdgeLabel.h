#ifndef PROCEDURAL_MODELING_EDGE_LABEL_H
#define PROCEDURAL_MODELING_EDGE_LABEL_H

#include "Face.h"
#include <iostream>
#include <string>

class EdgeLabel {
public:
  Face leftFace;
  Face rightFace;
  int angle;

  EdgeLabel();
  EdgeLabel(int a);
  EdgeLabel(int a, std::string left, std::string right);
  EdgeLabel(int a, Face left, Face right);
  EdgeLabel get_inverse() const;
};

std::ostream& operator <<(std::ostream& os, const EdgeLabel& edge_label);

#endif //PROCEDURAL_MODELING_EDGE_LABEL_H
