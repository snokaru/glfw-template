#ifndef _WINDOW_HPP
#define _WINDOW_HPP

#include "Color.hpp"
#include "Vector2f.hpp"
#include <GLFW/glfw3.h>
#include <string>


class Window {
private:
    GLFWwindow* window;
    int width;
    int height;
    std::string name;
public:
    Window(int width, int height, const std::string& name);
    bool should_close();
    void clear(Color);
    void display();    
};
#endif

