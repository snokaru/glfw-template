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
    const int SCREEN_HEIGHT = 800;
    Window* window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Chess Board");

    const int square_width = SCREEN_WIDTH / 8;
    const int square_height = SCREEN_HEIGHT / 8;

    while (!window->should_close()) {
        window->clear(Color(255, 255, 255));

        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                Color color = (i + j) % 2 == 0 ? Color(0, 0, 0) : Color(255, 255, 255);
                Rectangle square(Vector2f(i * square_width, j * square_height), Vector2f((i + 1) * square_width, (j + 1) * square_height), color);
                square.draw(window);
            }
        }
        

        window->display();
    }

    delete window;
    terminate();
    return 0;
}

