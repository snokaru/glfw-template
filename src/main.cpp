#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

struct Vector2f {
    float x;
    float y;
    Vector2f(float x, float y): x(x), y(y) {};
    void print(std::ostream& out) {
        out << "(" << this->x << ", " << this->y << ")";
    }
};

struct Vector3f {
    float x;
    float y;
    float z;
    Vector3f(float x, float y, float z): x(x), y(y), z(z) {}
    void print(std::ostream& out) {
        out << "(" << this->x << ", " << this->y << ", " << this->z << ")";
    }
};


void draw_triangle(Vector2f x, Vector2f y, Vector2f z, Vector3f color) {
    glBegin(GL_TRIANGLES);
        glColor3f(color.x, color.y, color.z);
        glVertex2f(x.x, x.y);
        glVertex2f(y.x, y.y);
        glVertex2f(z.x, z.y);
    glEnd();
}

void draw_circle(Vector2f center, float radius, Vector3f color, int steps = 1000) {
    for (int step = 0; step < steps; ++step) {
        float angle = (2 * M_PI * step) / steps;
        float next_angle = (2 * M_PI * (step + 1)) / steps;

        float x1 = radius * sin(angle); 
        float y1 = radius * cos(angle); 

        float x2 = radius * sin(next_angle); 
        float y2 = radius * cos(next_angle); 

        draw_triangle(center, Vector2f(x1, y1), Vector2f(x2, y2), color);
    }
}

void draw_rectangle(Vector2f p1, Vector2f p2, Vector3f color) {
    draw_triangle(p1, Vector2f(p2.x, p1.y), p2, color);
    draw_triangle(p1, Vector2f(p1.x, p2.y), p2, color);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }    

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        draw_circle(Vector2f(0, 0), 0.5, Vector3f(0, 1, 1));

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
