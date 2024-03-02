#ifndef PROCEDURAL_MODELING_EDGE_LABEL_H
#define PROCEDURAL_MODELING_EDGE_LABEL_H

#include "face.h"
#include <iostream>
#include <string>

class EdgeLabel {
public:
  face leftFace;
  face rightFace;
  int angle;

  EdgeLabel();
  EdgeLabel(int a);
  EdgeLabel(int a, std::string left, std::string right);
  EdgeLabel(int a, face left, face right);
  EdgeLabel get_inverse() const;
};

std::ostream& operator <<(std::ostream& os, const EdgeLabel& edge_label);

#endif //PROCEDURAL_MODELING_EDGE_LABEL_H
