#ifndef _SHAPE_HPP
#define _SHAPE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

#include "Color.hpp"
#include "Vector2f.hpp"
#include "Window.hpp"

class Shape {
public:
    virtual void draw(Window* window) = 0;
};

class Triangle: public Shape {
public:
    Triangle(Vector2f p1, Vector2f p2, Vector2f p3, Color color) : p1(p1), p2(p2), p3(p3), color(color) {}
    void draw(Window* window) {
        glBegin(GL_TRIANGLES);
            glColor4f(color.gl_r(), color.gl_g(), color.gl_b(), color.gl_a());
            glVertex2f(p1.x, p1.y);
            glVertex2f(p2.x, p2.y);
            glVertex2f(p3.x, p3.y);
        glEnd();
    }
private:
    Vector2f p1, p2, p3;
    Color color;
};

class Rectangle: public Shape {
public: 
    Rectangle(Vector2f p1, Vector2f p2, Color color): p1(p1), p2(p2), color(color) {};
    void draw(Window* window) {
        Triangle t1(p1, Vector2f(p2.x, p1.y), p2, color);
        Triangle t2(p1, Vector2f(p1.x, p2.y), p2, color);
        t1.draw(window);
        t2.draw(window);
    }
private:
    Vector2f p1, p2;
    Color color;
};

class Circle: public Shape {
public:
    Circle(Vector2f center, int radius, Color color, int steps = 1000): center(center), radius(radius), color(color), steps(steps) {};
    void draw(Window* window) {
        for (int step = 0; step < steps; ++step) {
            float angle = (2 * M_PI * step) / steps;
            float next_angle = (2 * M_PI * (step + 1)) / steps;
            // std::cout << angle << '\n';

            float x1 = center.x + radius * sin(angle); 
            float y1 = center.y + radius * cos(angle); 

            float x2 = center.x + radius * sin(next_angle); 
            float y2 = center.y + radius * cos(next_angle); 

            Triangle triangle(center, Vector2f(x1, y1), Vector2f(x2, y2), color); triangle.draw(window);
        }
    }
private:
    Vector2f center;
    int radius;
    Color color;
    int steps;
};

#endif
