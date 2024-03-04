#include <iostream>
#include <vector>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Input.h"
#include "Graph.h"
#include "Primitive.h"

const int WINDOW_X = 100;
const int WINDOW_Y = 100;
int window_w = 1000;
int window_h = 1000;
Graph g;

void display();

void initWindow(int argc, char** argv) {
  std::cerr << "[INFO] Starting OpenGL main loop." << std::endl;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
  glutInitWindowSize(window_w, window_h);
  glutInitWindowPosition(WINDOW_X, WINDOW_Y);
  glutCreateWindow("Window 1");

  glutDisplayFunc(display);
}

int main(int argc, char ** argv){
  load_graph(g);

  // Split graph into primitives
  std::vector<Primitive> primitives;
  g.split_primitives(primitives);
  for (const Primitive& p: primitives) {
    std::cout << p << std::endl;
  }

  initWindow(argc, argv);
  glutMainLoop();
  std::cerr << "[INFO] Exit OpenGL main loop." << std::endl;
  return 0;
}
void display(){
  std::cerr << "[INFO] Running loop." << std::endl;
  // Probably necessary to make background white for exports.
  // glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);

  // This zooms the camera out a bit, probably more complex than needed.
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective (90, 1, 1, 3);
  glOrtho(-1, 1, -1.0, 1, 1, 3);

  gluLookAt(0.0, 0.0, 0.0,
            0.0, 0.0, -1.0,
            0.0, 1.0, 0.0);

  g.draw();

  glFlush();
}