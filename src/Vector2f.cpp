#include "Vector2f.hpp"

Vector2f::Vector2f(float x, float y)
: x(x), y(y) {}

float Vector2f::getX() {
  return x;
}

float Vector2f::getY() {
  return y;
}

void Vector2f::setX(float x) {
  this->x = x;
}

void Vector2f::setY(float y) {
  this-> y = y;
}

