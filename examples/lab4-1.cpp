#include <stb_image.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include <opengllib/Color.hpp>
#include <opengllib/Window.hpp>
#include <opengllib/Vector2f.hpp>
#include <opengllib/Vector3f.hpp>
#include <opengllib/Shape.hpp>
#include <opengllib/Texture2D.hpp>
#include <opengllib/Sprite.hpp>

void init() {
    glfwInit();
}

void terminate() {
    glfwTerminate();
}

int main() {
    init();
    const int SCREEN_WIDTH = 700;
    const int SCREEN_HEIGHT = 700;
    Window* window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "House");
    Texture2D texture("./container.jpg");
    std::cout << "loaded texture\n";
    Rectangle house(Vector2f(200, 200), Vector2f(600, 500), Color(0, 0, 255));
    Sprite wood_sprite(texture);
    wood_sprite.set_position(Vector2f(100, 100));

    while (!window->should_close()) {
        window->clear(Color(255, 255, 255));

        // house.draw(window);
        wood_sprite.draw();
        window->display();
    }

    delete window;
    terminate();
    return 0;
}

