#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
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

