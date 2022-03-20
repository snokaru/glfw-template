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
    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 800;
    Window* window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Replacing Textures");

    Color* white_pixels = new Color[SCREEN_WIDTH * SCREEN_HEIGHT];
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; ++i) 
        white_pixels[i] = Color(255, 255, 255);

    Texture2D white_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
    white_texture.update(white_pixels);
    
    Texture2D black_texture(SCREEN_WIDTH / 8, SCREEN_HEIGHT / 8);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if((i + j) % 2 == 0) {
                std::cout << "black square at (" << i * (SCREEN_WIDTH / 8) << "," << j * (SCREEN_HEIGHT / 8) << ")\n";
                white_texture.update(black_texture, Vector2f(i * (SCREEN_WIDTH / 8), j * (SCREEN_HEIGHT / 8)));
            }
        }
    }

    white_texture.update(black_texture, Vector2f(200, 200));
    white_texture.update(black_texture, Vector2f(400, 400));
    Sprite chessboard(white_texture);

    while (!window->should_close()) {
        window->clear(Color(0, 0, 0));
        
        chessboard.draw();

        window->display();
    }

    delete window;
    terminate();
    return 0;
}

