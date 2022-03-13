#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Color.hpp"
#include "Vector2f.hpp"
#include "Window.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
}

Window::Window(int width, int height, const std::string& name): width(width), height(height), name(name) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
    if (!window) {
        std::cout << "Could not create window!\n";
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n"; 
        exit(-1);
    }    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
}

bool Window::should_close() {
    return glfwWindowShouldClose(window);
}

void Window::clear(Color color) {
    glClearColor(color.gl_r(), color.gl_g(), color.gl_b(), color.gl_a());
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::display() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

