#include <iostream>
#include <string>

#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <stb_image.h>

#include <opengllib/Texture2D.hpp>

Texture2D::Texture2D(std::string filename, bool mipmapped)
: filename(filename), mipmapped(mipmapped){

    glGenTextures(1, &texture_id);
    this->bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);

    data = stbi_load(filename.c_str(), &width, &height, &number_of_channels, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glEnable(GL_TEXTURE_2D);
}

Texture2D::~Texture2D() {
    stbi_image_free(this->data);
}

void Texture2D::bind() const {
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

Texture2D::Texture2D(int width, int height)
:width(width), height(height) {
    glGenTextures(1, &texture_id);
    this->bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, 
                   GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
                   GL_NEAREST);

    data = new unsigned char[width * height * 3];
    for (int i = 0; i < width * height * 3; ++i) {
        data[i] = 0;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glEnable(GL_TEXTURE_2D);
}

void Texture2D::update(Color* pixels) {
    this->bind();
    for (int i = 0, j = 0; i < width * height * 4; i+=4, j++) {
        data[i] = pixels[j].r;
        data[i + 1] = pixels[j].g;
        data[i + 2] = pixels[j].b;
        data[i + 3] = pixels[j].a;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void Texture2D::update(const Texture2D& other_texture, Vector2f position) {
    this->bind();
    glTexSubImage2D(GL_TEXTURE_2D, 0, position.x, position.y, other_texture.get_width(), other_texture.get_height(), GL_RGB, GL_UNSIGNED_BYTE, other_texture.get_raw_data());
}

