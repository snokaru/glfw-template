#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <opengllib/App.hpp>

App::App(int width, int height) {
  this->width = width;
  this->height = height;
}

void App::run() {
  char *glut_argv[] = { 
    (char *)"", 
    (char *)0  
  };
  int glut_argc = 0; 

  glutInit(&glut_argc, glut_argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(width, height);
  glutCreateWindow("Window");

  this->init();
  glutDisplayFunc();

  glutMainLoop();
}

void App::run() {
}
