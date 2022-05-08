#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <opengllib/Texture2D.hpp>
#include <cmath>

#include <iostream>

#define FPS 60

const int width = 16*100;
const int height = 9*100;

void display();
void reshape(int w,int h);
void timer(int);
void passive_motion(int,int);
void camera();
void keyboard(unsigned char key,int x,int y);
void keyboard_up(unsigned char key,int x,int y);

void init()
{
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glutWarpPointer(width/2,height/2);
}

int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Projectile Motion - 3D Simulation");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0,timer,0); 
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);

    glutMainLoop();
   
    return 0;
}

void draw()
{
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    draw();
    glutSwapBuffers();
}

void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60,16.0/9.0,1,75);
    glMatrixMode(GL_MODELVIEW);

}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer,0);
}

