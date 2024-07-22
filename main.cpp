#include <iostream>
#include <vector>
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

#include "Input.h"
#include "InputGraph.h"
#include "Primitive.h"
#include "Rule.h"
#include "CameraTrackball.h"
#include "GraphIsomorphism.h"
#include "GraphTransform.h"

const int WINDOW_X = 100;
const int WINDOW_Y = 100;
int window_w = 1000;
int window_h = 1000;
const float FOV_Y = 60.0f;
const float NEAR_CLIP = 0.1f;
const float FAR_CLIP = 100.0f;
const int FPS = 30;
// Inputs
int mouse_x = 0;
int mouse_y = 0;
int mouse_buttons[GLUT_NUM_MOUSE_BUTTONS];
// Camera
CameraTrackball camera;

InputGraph g;
Graph outputGraph;
std::vector<Rule> testRules;
std::vector<Primitive> primitives;

void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  camera.lookAt();

//  for (const Primitive &p: primitives) {
//    p.draw();
//  }
//  g.draw();
  outputGraph.draw();

  glutSwapBuffers();
}

void reshape(int w, int h) {
  window_w = w; window_h = h;
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(FOV_Y, (GLfloat)w / (GLfloat)h, NEAR_CLIP, FAR_CLIP);
}

void mouseButton(int button, int state, int x, int y) {
  // Scroll wheel not really working
  mouse_buttons[button] = state;

  // Update camera
  camera.zoom(mouse_buttons[3] - mouse_buttons[4]);
}

void mousePassiveMotion(int x, int y) {
  mouse_x = x; mouse_y = y;
}

void mouseMotion(int x, int y) {
  int mouse_dx = mouse_x - x; int mouse_dy = mouse_y - y;
  float dxn = static_cast<float>(mouse_dx) / static_cast<float>(window_w);
  float dyn = -static_cast<float>(mouse_dy) / static_cast<float>(window_h);
  mouse_x = x; mouse_y = y;

  // Update camera
  if (mouse_buttons[GLUT_LEFT_BUTTON] == GLUT_DOWN)  camera.rotate(dxn, dyn);
  if (mouse_buttons[GLUT_RIGHT_BUTTON] == GLUT_DOWN) camera.pan(dxn, dyn, 0.0f);
}

void keyBoardInput(unsigned char key, int x, int y) {
  switch(key) {
    case '-':
      camera.zoom(1);
      break;
    case '+':
      camera.zoom(-1);
      break;
    case 'n':
//      add_square(g, g.vertices.back().pos.x, g.vertices.back().pos.y, 1);
      applyRandomRule(testRules, outputGraph);
      break;
  }
}

void timer(int v) {
  glutPostRedisplay();
  glutTimerFunc(1000 / FPS, timer, 0);
}

void initWindow(int argc, char** argv) {
  std::cerr << "[INFO] Starting OpenGL main loop." << std::endl;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(window_w, window_h);
  glutInitWindowPosition(WINDOW_X, WINDOW_Y);
  glutCreateWindow("Window 1");

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);
  glShadeModel(GL_SMOOTH);

  // Init inputs
  for (int & mouse_button : mouse_buttons) {mouse_button = GLUT_UP;}

  // Init camera
  camera.init({0.0f,0.0f,0.0f}, 10.0f);

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);

  glutMouseFunc(mouseButton);
  glutPassiveMotionFunc(mousePassiveMotion);
  glutMotionFunc(mouseMotion);
  glutKeyboardFunc(keyBoardInput);
  glutTimerFunc(1000 / FPS, timer, 0);
}

int main(int argc, char ** argv){
  load_graph(g);

  // Split graph into primitives
  g.split_primitives(primitives);
  for (const Primitive& p: primitives) {
    std::cout << p << std::endl;
  }

  load_square_alt(outputGraph);
  load_square_rules(testRules);
//  testIsomorphism();
//  testGraphTransform();

  initWindow(argc, argv);
  glutMainLoop();
  std::cerr << "[INFO] Exit OpenGL main loop." << std::endl;
  return 0;
}
