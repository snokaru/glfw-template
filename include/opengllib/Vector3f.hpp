#ifndef _VECTOR3F_HPP
#define _VECTOR3F_HPP

#include <iostream>

struct Vector3f {
    float x;
    float y;
    float z;
    Vector3f(float x = 0, float y = 0, float z = 0): x(x), y(y), z(z) {}
    Vector3f operator+(const Vector3f& rhs) {
      return Vector3f(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z); 
    }
    Vector3f operator-(const Vector3f& rhs) const {
      return Vector3f(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z); 
    }
    float operator*(const Vector3f& rhs) const {
      return this->x * rhs.x + this->y * rhs.y + this->z * rhs.z; 
    }
    Vector3f dot(const Vector3f& rhs) const {
      return Vector3f(this->x * rhs.x,this->y * rhs.y, this->z * rhs.z); 
    }
};



#endif
