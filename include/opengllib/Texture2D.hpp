#ifndef _TEXTURE2D_HPP
#define _TEXTURE2D_HPP

#include <string>
#include <opengllib/Color.hpp>
#include <opengllib/Vector2f.hpp>

#include <OpenGL/gl.h>
#include <GLUT/glut.h>

class Texture2D {
public:
    Texture2D(std::string filename, bool mipmapped=false);
    Texture2D(int width, int height);
    void bind() const;
    void update(Color* pixels);
    void update(const Texture2D& other_texture, Vector2f position);
    unsigned char* get_raw_data() const { return data; }
    int get_width() const { return width; }
    int get_height() const { return height; }
    ~Texture2D();
    void enable() {
      glEnable(GL_TEXTURE); 
    }
    void disable() {
      glDisable(GL_TEXTURE); 
    }
private:
    std::string filename;
    bool mipmapped;

    GLuint texture_id;
    int width, height;
    int number_of_channels;

    unsigned char* data;
};

#endif

