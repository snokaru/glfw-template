#ifndef _TEXTURE2D_HPP
#define _TEXTURE2D_HPP

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Texture2D {
public:
    Texture2D(std::string filename, bool mipmapped=false);
    void bind() const;
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    ~Texture2D();
private:
    std::string filename;
    bool mipmapped;

    GLuint texture_id;
    int width, height;
    int number_of_channels;

    unsigned char* data;
};

#endif

