#ifndef PROCEDURAL_MODELING_FACE_H
#define PROCEDURAL_MODELING_FACE_H

#include <iostream>
#include <string>

class Face {
public:
  std::string id;

  Face();
  Face(std::string s);
};

std::ostream& operator <<(std::ostream& os, const Face& f);

#endif //PROCEDURAL_MODELING_FACE_H