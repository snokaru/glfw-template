#ifndef _SPRITE_HPP
#define _SPRITE_HPP

#include <opengllib/Texture2D.hpp>
#include <opengllib/Shape.hpp>

class Sprite {
public:
    Sprite(const Texture2D& texture);
    void draw();
    void set_position(Vector2f position) {
        this->position = position;
    };
private:
    const Texture2D& texture;
    Vector2f position;
};

#endif
