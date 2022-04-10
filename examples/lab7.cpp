#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <opengllib/Texture2D.hpp>


void display() {  
    glEnable(GL_TEXTURE);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
 
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    Texture2D texture = Texture2D("wood.jpg");
    texture.bind();

    GLUquadric* sun = gluNewQuadric();
    gluQuadricTexture(sun, true);
    gluSphere(sun, 0.2, 64, 64);
    gluDeleteQuadric(sun);

    glFlush();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    double ratio = (double) width / (double) height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(38, ratio, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
}

void init() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);     
    glutInitWindowPosition(100, 100); 
    glutCreateWindow("GL RGB Triangle");
    init();
    glutDisplayFunc(display);          
    glutReshapeFunc(reshape);
    
    glutMainLoop();
                   
    return 0;

}

