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

    const int SQUARE_WIDTH = 100;
    const int SQUARE_HEIGHT = 100;
    Window* window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Textures");

    Color* pixels_canvas = new Color[SQUARE_WIDTH * SQUARE_HEIGHT];

    for (int i = 0; i < SQUARE_WIDTH * SQUARE_HEIGHT; ++i) 
        pixels_canvas[i] = Color(255, 255, 0, 100);
    Texture2D red_texture(100, 100);
    red_texture.update(pixels_canvas);

    for (int i = 0; i < SQUARE_WIDTH * SQUARE_HEIGHT; ++i) 
        pixels_canvas[i] = Color(0, 0, 255, 50);
    Texture2D blue_texture(100, 100);
    blue_texture.update(pixels_canvas);

    Sprite red_sprite(red_texture);
    red_sprite.set_position(Vector2f(100, 100));

    Sprite blue_sprite(blue_texture);
    blue_sprite.set_position(Vector2f(100, 100));

    while (!window->should_close()) {
        window->clear(Color(255, 255, 255));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        red_sprite.set_position(Vector2f(100, 100));
        red_sprite.draw();
        blue_sprite.set_position(Vector2f(100, 100));
        blue_sprite.draw();

        glDisable(GL_BLEND);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        red_sprite.set_position(Vector2f(300, 100));
        red_sprite.draw();
        blue_sprite.set_position(Vector2f(300, 100));
        blue_sprite.draw();

        glDisable(GL_BLEND);

        glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        red_sprite.set_position(Vector2f(500, 100));
        red_sprite.draw();
        blue_sprite.set_position(Vector2f(500, 100));
        blue_sprite.draw();

        glDisable(GL_BLEND);

        red_sprite.set_position(Vector2f(500, 100));
        red_sprite.draw();
        blue_sprite.set_position(Vector2f(500, 100));
        blue_sprite.draw();

        red_sprite.set_position(Vector2f(100, 300));
        red_sprite.draw();
        blue_sprite.set_position(Vector2f(100, 300));
        blue_sprite.draw();

        red_sprite.set_position(Vector2f(100, 500));
        red_sprite.draw();
        blue_sprite.set_position(Vector2f(100, 500));
        blue_sprite.draw();

        // house.draw(window);
        window->display();
    }

    delete window;
    terminate();
    return 0;
}

