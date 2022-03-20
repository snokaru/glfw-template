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
    Window* window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Textures");

    Texture2D container_texture("./container.jpg");
    Texture2D wood_texture("./wood.jpg");

    Sprite wood_sprite(wood_texture);
    wood_sprite.set_position(Vector2f(100, 100));

    Sprite container_sprite(container_texture);
    container_sprite.set_position(Vector2f(500, 100));

    while (!window->should_close()) {
        window->clear(Color(255, 255, 255));

        // house.draw(window);
        wood_sprite.draw();
        container_sprite.draw();
        window->display();
    }

    delete window;
    terminate();
    return 0;
}

