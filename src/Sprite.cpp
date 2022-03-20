#include <opengllib/Sprite.hpp>
#include <opengllib/Texture2D.hpp>

#include <iostream>

Sprite::Sprite(const Texture2D& texture)
: texture(texture), position(Vector2f(0, 0)) {}

void Sprite::draw() {
    texture.bind();
    int width = texture.get_width(), height = texture.get_height();
    glBegin(GL_QUADS);
        // Lower left corner.
        glTexCoord2f(0, 1);
        glVertex2f(position.x, position.y + height);

        // Lower right corner.
        glTexCoord2f(1, 1);
        glVertex2f(position.x + width, position.y + height);

        // Upper right corner.
        glTexCoord2f(1, 0);
        glVertex2f(position.x + width, position.y);

        // Upper left corner.
        glTexCoord2f(0, 0);
        glVertex2f(position.x, position.y);
    glEnd();
}

const Texture2D& Sprite::get_texture() {
    return texture;
}
