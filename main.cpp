#include <iostream>
#include <vector>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Input.h"
#include "Graph.h"
#include "Primitive.h"

void display();
void initCanvas(int argc, char ** argv) {
  std::cerr << "[INFO] Starting OpenGL main loop." << std::endl;
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Window 1");

  glutDisplayFunc(display);
}
void canvasLoop() {
  glutMainLoop();
  std::cerr << "[INFO] Exit OpenGL main loop." << std::endl;
}


int main(int argc, char ** argv){
  Graph g;
  load_graph(g);

  // Split graph into primitives
  std::vector<Primitive> primitives;
  g.split_primitives(primitives);
  for (const Primitive& p: primitives) {
    std::cout << p << std::endl;
  }

  initCanvas(argc, argv);
  canvasLoop();
  return 0;
}
void display(){
  std::cerr << "[INFO] Running loop." << std::endl;
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_POLYGON);
  glVertex3f(-0.5, -0.5, 0);
  glVertex3f( 0.5, -0.5, 0);
  glVertex3f( 0.5,  0.5, 0);
  glVertex3f(-0.5,  0.5, 0);
  glEnd();
  glFlush();
}