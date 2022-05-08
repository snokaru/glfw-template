#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <opengllib/Texture2D.hpp>

Texture2D* sun_texture;
Texture2D* moon_texture;
Texture2D* earth_texture;
Texture2D* earth_clouds_texture;

void draw_sphere(const Texture2D& texture, float radius) {
    texture.bind();
    glEnable(GL_TEXTURE);
    GLUquadric* sphere = gluNewQuadric();
    gluQuadricTexture(sphere, true);
    gluSphere(sphere, radius, 64, 64);
    gluDeleteQuadric(sphere);
}

void display() {  
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 0x1, 0x1);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0, -0.5);
    glEnd();
    glStencilFunc(GL_EQUAL, 0x1, 0x1);

    static GLfloat moon_rotation = 0;
    static GLfloat earth_rotation = 0;
    GLfloat light_pos[] = {0, 0, 0, 1};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    // gluLookAt(0, 300, -300, 0, 0, -300, 1, 0, 0);

    glTranslatef(0, 0, -300);

    glDisable(GL_LIGHTING);
    draw_sphere(*sun_texture, 30);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    glRotatef(earth_rotation, 0, 1, 0);
    glTranslatef(105, 0, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    draw_sphere(*earth_texture, 15);
    draw_sphere(*earth_clouds_texture, 15);

    glRotatef(moon_rotation, 0, 1, 0);
    glTranslatef(30, 0, 0);
    glColor3ub(200, 200, 200);
    draw_sphere(*moon_texture, 6);

    glPopMatrix();

    earth_rotation += 1;
    moon_rotation += 2;
    if (earth_rotation > 360) earth_rotation = 0;
    if (moon_rotation > 360) moon_rotation = 0;

    glutSwapBuffers();
    
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);

    GLfloat aspect_ratio = (GLfloat) width / (GLfloat) height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, aspect_ratio, 1, 425);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
        
}

void init() {
    GLfloat white_light[] = {0.2, 0.2, 0.2, 1};
    GLfloat source_light[] = {0.8, 0.8, 0.8, 1};
    GLfloat light_position[] = {0, 0, 0, 1};

    sun_texture = new Texture2D("sun.jpg");
    earth_texture = new Texture2D("earth.jpg");
    moon_texture = new Texture2D("moon.jpg");
    earth_clouds_texture= new Texture2D("earth_clouds_texture.jpg");
    
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white_light);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, source_light);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glEnable(GL_TEXTURE);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);                
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);                


}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(1, timer, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(800, 600);     
    glutCreateWindow("Simple");
    glutDisplayFunc(display);          
    glutReshapeFunc(reshape);
    glutTimerFunc(1, timer, 1);

    init();
    glutMainLoop();
                   
    return 0;

}

