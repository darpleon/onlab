#pragma once

#include "Controller.hpp"
#include <GLFW/glfw3.h>
namespace Context {

constexpr unsigned int SCR_WIDTH = 1000;
constexpr unsigned int SCR_HEIGHT = 1000;

GLFWwindow* init();

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow *window);

void add_listener(Controller* listener);

void update();

void rotate(float angle);

}
