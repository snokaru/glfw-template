#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include "Color.hpp"
#include "Window.hpp"
#include "Vector2f.hpp"
#include "Vector3f.hpp"
#include "Shape.hpp"


void init() {
    glfwInit();
}

void terminate() {
    glfwTerminate();
}

int main() {
    init();
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    Window* window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Learn OpenGL");
    Rectangle house(Vector2f(200, 200), Vector2f(600, 500), Color(0, 0, 255));
    Triangle roof(Vector2f(200, 200), Vector2f(600, 200), Vector2f(400, 100), Color(255, 0, 0));
    Rectangle door(Vector2f(300, 350), Vector2f(400, 500), Color(0, 255, 0));
    Circle door_knob(Vector2f(385, 450), 10, Color(255, 0, 0));

    while (!window->should_close()) {
        window->clear(Color(255, 255, 255));
        
        // rect.draw(window);
        // triangle.draw(window);
        house.draw(window);
        roof.draw(window);
        door.draw(window);
        door_knob.draw(window);

        window->display();
    }

    delete window;
    terminate();
    return 0;
}

