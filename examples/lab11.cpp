#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <opengllib/Texture2D.hpp>
#include <cmath>
#include <cstdlib>

#include <iostream>


const int width = 800;
const int height = 600;
const int PARTICLES_COUNT = 5000;
int cam_x = -10, cam_y = 0, cam_z = 10;

void display();
void init();
void reshape(int w,int h);
void timer(int);

class Particle {
private:

  double position_x, position_y, position_z;
  double speed_x, speed_y, speed_z;
  double accel_x, accel_y, accel_z;
  double radius;
  double life;

  Texture2D* texture;

public:

  Particle(Texture2D* texture = nullptr) {
    this->texture = texture;
    this->init();
  }

  void set_texture(Texture2D* texture) {
    this->texture = texture;
  }

  void init() {
    this->position_x = 0;
    this->position_y = rand() % 100;
    this->position_z = 0;

    int direction_x = rand() % 2 >= 1 ? 1 : -1;
    int direction_y = rand() % 2 >= 1 ? 1 : -1;
    int direction_z = rand() % 2 >= 1 ? 1 : -1;

    this->accel_x = direction_x * rand() % 1;
    this->accel_y = direction_y * rand() % 1;
    this->accel_z = direction_z * rand() % 1;

    this->speed_x = direction_x * rand() % 2;
    this->speed_y = direction_y * rand() % 2;
    this->speed_z = direction_z * rand() % 2;

    this->life = rand() % 50;
    this->radius = 2;

  }

  void update(double cam_x, double cam_y, double cam_z) {
    this->speed_x += this->accel_x / 10;
    this->speed_y += this->accel_y / 10;
    this->speed_z += this->accel_z / 10;

    this->position_x += this->speed_x;
    this->position_y += this->speed_y;
    this->position_z += this->speed_z;

    this->life -= 0.5;

    if (this->life <= 0)
      this->init();
  }

  void draw() {
    texture->bind();
    texture->enable();

    GLfloat mv[16];
    glGetFloatv(GL_MODELVIEW_MATRIX, mv);

    // clear rotation from modelview matrix
    // http://www.lighthouse3d.com/opengl/billboarding/index.php?billCheat
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (i == j) mv[i * 4 + j] = 1;
        else        mv[i * 4 + j] = 0;
      }
    }


    glPushMatrix();
      glLoadMatrixf(mv);
      glBegin(GL_POLYGON);
        glTexCoord2d(0, 0);
        glVertex3d(position_x - radius, position_y - radius, position_z);
        glTexCoord2d(1, 0);
        glVertex3d(position_x + radius, position_y - radius, position_z);
        glTexCoord2d(1, 1);
        glVertex3d(position_x + radius, position_y + radius, position_z);
        glTexCoord2d(0, 1);
        glVertex3d(position_x - radius, position_y + radius, position_z);
      glEnd();
    glPopMatrix();

    texture->disable();
  }
};

Particle particles[PARTICLES_COUNT];

int main(int argc,char**argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("Window");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(1,timer,1); 

    glutMainLoop();
   
    return 0;
}

void init()
{
    static Texture2D texture("fire.png");
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 0);
    for (int i = 0; i < PARTICLES_COUNT; ++i) {
      particles[i].set_texture(&texture); 
    }
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

}

void update() {
    for (int i = 0; i < PARTICLES_COUNT; ++i) {
      particles[i].update(cam_x, cam_y, cam_z);
    }
}

void draw()
{
    gluLookAt(cam_x, cam_y, cam_z, 0, cam_y, 0, 0, 1, 0);
    for (int i = 0; i < PARTICLES_COUNT; ++i) {
      particles[i].draw();
    }
    glColor3f(1, 1, 1);

    glBegin(GL_LINES);
      glVertex3f(0, 0, 0);
      glVertex3f(50, 0, 0);
    
      glVertex3f(0, 0, 0);
      glVertex3f(0, 50, 0);
    
      glVertex3f(0, 0, 0);
      glVertex3f(0, 0, 50);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    update();
    draw();
    glutSwapBuffers();
}

void reshape(int w,int h)
{
    glViewport(0, 0, w, h);
    double ratio = (double) w / h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, ratio, 1, 200);
    glMatrixMode(GL_MODELVIEW);

}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1, timer, 1);
}

