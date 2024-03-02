#ifndef PROCEDURAL_MODELING_FACE_H
#define PROCEDURAL_MODELING_FACE_H

#include <iostream>
#include <string>

class face {
public:
  std::string id;

  face();
  face(std::string s);
};

std::ostream& operator <<(std::ostream& os, const face& f);

#endif //PROCEDURAL_MODELING_FACE_H