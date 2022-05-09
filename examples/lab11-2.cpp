#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <opengllib/Texture2D.hpp>

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <ctime>


const int width = 800;
const int height = 600;
const int SPHERES_COUNT = 50;
int cam_x = 60, cam_y = 0, cam_z = 80;


std::ostream& operator<<(std::ostream& out, const Vector3f& v) {
  return out << "(" << v.x << "," << v.y << "," << v.z << ")";
}

class Plane;

class Sphere {
private:
  Vector3f position;
  Vector3f speed;
  GLUquadric* quadric;
  int radius;
public:
  Sphere(Vector3f position) {
    int pos_interval = 10;
    this->position = position;

    int speed_interval = 5;
    this->speed.x = (float) (rand() % speed_interval - speed_interval / 2) / 10;
    this->speed.y = (float) (rand() % speed_interval - speed_interval / 2) / 10;
    this->speed.z = (float) (rand() % speed_interval - speed_interval / 2) / 10;
    //
    // this->speed.x = 0.1;
    // this->speed.y = 0;
    // this->speed.z = 0;

    this->radius = 2;
    this->quadric = gluNewQuadric();
  }

  void update() {
    position = position + speed;
  }

  Vector3f get_position() {
    return position;
  }

  Vector3f get_speed() {
    return speed;
  }

  int get_radius() {
    return radius;
  }

  bool collides_with(const Sphere& other) {
    int r_squared = (this->radius - other.radius) * (this->radius - other.radius);
    float distance = (other.position - this->position) * (other.position - this->position);
    return distance < r_squared;
  }

  void render() {
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glColor3ub(255, 0, 0);
    gluSphere(quadric, radius, 64, 64);
    glPopMatrix();
  }

  ~Sphere() {
    gluDeleteQuadric(quadric);
  }

  friend bool solve_collision(Sphere&, Plane&);
  friend bool solve_collision(Sphere& first, Sphere& second);
};


class Plane {
private:
  Vector3f point, v1, v2;
  Color color;
public:
  Plane(Vector3f point, Vector3f v1, Vector3f v2, Color color) {
    this->point = point;
    this->v1 = v1;
    this->v2 = v2;
    this->color = color;
  }

  void render() {
    glColor4ub(color.r, color.g, color.b, color.a);
    glBegin(GL_QUADS); 
      glVertex3f(point.x, point.y, point.z);
      glVertex3f(point.x + v1.x, point.y + v1.y, point.z + v1.z);
      glVertex3f(point.x + v1.x + v2.x, point.y + v1.y + v2.y, point.z + v1.z + v2.z);
      glVertex3f(point.x + v2.x, point.y + v2.y, point.z + v2.z);
    glEnd();
  }
  Vector3f normal() {
  }
  friend bool solve_collision(Sphere&, Plane&);
};

bool solve_collision(Sphere& first, Sphere& second) {
    int r_squared = (first.radius + second.radius) * (first.radius + second.radius);
    float distance = (first.position - second.position) * (first.position - second.position);
    // std::cout << "distance is " << distance << '\n';
    return distance < r_squared;
}

bool solve_collision(Sphere& sphere, Plane& plane) {
    // std::cout << "sphere pos " << sphere.position << '\n';
    
    // compute equation of plane
    // https://www.geeksforgeeks.org/program-to-find-equation-of-a-plane-passing-through-3-points/
    Vector3f v2 = plane.point + plane.v2;
    Vector3f v1 = plane.point + plane.v1;
    // std::cout << "points are " << v1 << "," << v2 << "," << plane.point << '\n';

    Vector3f first_side = v2 - plane.point;
    Vector3f second_side = v1 - plane.point;

    float a = first_side.y * second_side.z - first_side.z * second_side.y;
    float b = second_side.x * first_side.z - first_side.x * second_side.z;
    float c = first_side.x * second_side.y - first_side.y * second_side.x;
    float d = - a * plane.point.x - b * plane.point.y - c * plane.point.z; 
    // std::cout << "plane equation: " << a << "x+" << b << "y+" << c << "z=" << d << '\n';


    // https://stackoverflow.com/questions/63103184/sphere-plane-collision-resolve
    // https://stackoverflow.com/questions/22093749/c-plane-sphere-collision-detection
    float wl = sqrt(a * a + b * b + c * c);
    float distance = (a * sphere.position.x + b * sphere.position.y + c * sphere.position.z + d) / wl;
    distance = abs(distance);


    bool colliding = distance < sphere.radius;

    if (!colliding) {
      return false;
    }

    float nx = a / wl;
    float ny = b / wl;
    float nz = c / wl;

    float scope = (sphere.speed.x * nx + sphere.speed.y * ny + sphere.speed.z * nz) * 2;

    nx *= scope;
    ny *= scope;
    nz *= scope;
    
    Vector3f next_speed;
    next_speed.x = sphere.speed.x - nx;
    next_speed.y = sphere.speed.y - ny;
    next_speed.z = sphere.speed.z - nz;

    sphere.speed = next_speed;


    return true;
}

static std::vector<Sphere*> spheres;
static std::vector<Plane*> planes;

void display();
void init();
void reshape(int w,int h);
void timer(int);

int main(int argc,char**argv)
{
    srand (time(NULL));
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
    Color red(255, 0, 0, 120); 
    Color green(0, 255, 0, 120);
    Color blue(0, 0, 255, 120);
    Color yellow(255, 255, 0, 120);
    Color purple(255, 0, 255, 120);
    Color cyan(0, 255, 255, 120);
    int cube_size = 50;
    int half_cube_size = cube_size / 2;
    Vector3f cube_center(0, 0, 0);
    for (int i = 0; i < SPHERES_COUNT; i++) {
      int radiused_cube_size = cube_size - 5;
      int x = rand() % (radiused_cube_size - 10) - radiused_cube_size / 2;
      int y = rand() % (radiused_cube_size - 10) - radiused_cube_size / 2;
      int z = rand() % (radiused_cube_size - 10) - radiused_cube_size / 2;
      spheres.push_back(new Sphere(Vector3f(x, y, z)));
    }
    planes.push_back(new Plane(
      Vector3f(cube_center.x - half_cube_size, cube_center.y - half_cube_size, cube_center.z + half_cube_size),
      Vector3f(0, 0, -cube_size),
      Vector3f(0, cube_size, 0),
      red
    ));
    planes.push_back(new Plane(
      Vector3f(cube_center.x - half_cube_size, cube_center.y - half_cube_size, cube_center.z + half_cube_size),
      Vector3f(0, 0, -cube_size),
      Vector3f(cube_size, 0, 0),
      blue
    ));
    planes.push_back(new Plane(
      Vector3f(cube_center.x - half_cube_size, cube_center.y - half_cube_size, cube_center.z - half_cube_size),
      Vector3f(cube_size, 0, 0),
      Vector3f(0, cube_size, 0),
      purple
    ));
    planes.push_back(new Plane(
      Vector3f(cube_center.x - half_cube_size, cube_center.y + half_cube_size, cube_center.z + half_cube_size),
      Vector3f(0, 0, -cube_size),
      Vector3f(cube_size, 0, 0),
      yellow
    ));
    planes.push_back(new Plane(
      Vector3f(cube_center.x + half_cube_size, cube_center.y - half_cube_size, cube_center.z - half_cube_size),
      Vector3f(0, 0, cube_size),
      Vector3f(0, cube_size, 0),
      cyan
    ));
    planes.push_back(new Plane(
      Vector3f(cube_center.x - half_cube_size, cube_center.y - half_cube_size, cube_center.z + half_cube_size),
      Vector3f(cube_size, 0, 0),
      Vector3f(0, cube_size, 0),
      green
    ));
    glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glClearColor(1, 1, 1, 1);
    glClearDepth(1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

}

void update() 
{
  for (int i = 0; i < spheres.size(); ++i) {
    spheres[i]->update();
    for (Plane* plane: planes) {
      solve_collision(*spheres[i], *plane);
    }

    int sphere_that_collides = -1;
    for (int j = i + 1; j < spheres.size(); j++){
      if (i == j) continue;
      // std::cout << "checking collission between " << i << " and " << j << '\n';
      if (solve_collision(*spheres[i], *spheres[j])) {
        // std::cout << "COLLIDES!" << '\n';
        sphere_that_collides = j;
        break;
      }
    }
    if (sphere_that_collides != -1) {
      delete spheres[i];
      delete spheres[sphere_that_collides];
      spheres.erase(spheres.begin() + i);
      spheres.erase(spheres.begin() + sphere_that_collides - 1);
      i--;
    }
  }
}

void draw()
{
  gluLookAt(cam_x, cam_y, cam_z, 0, cam_y, 0, 0, 1, 0);
  glColor3f(.5, .5, .5);
  for (Sphere* sphere: spheres) {
    sphere->render();
  }
  for (Plane* plane: planes) {
    plane->render();
  }
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

