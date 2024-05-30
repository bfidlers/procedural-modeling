#ifndef PROCEDURAL_MODELING_INPUT_H
#define PROCEDURAL_MODELING_INPUT_H

#include "InputGraph.h"

#include <iostream>
#include <vector>

void load_triangle(InputGraph& g);
void load_square(InputGraph& g);
void add_square(InputGraph& g, float x, float y, float size);
void load_graph(InputGraph& g);

#endif //PROCEDURAL_MODELING_INPUT_H
