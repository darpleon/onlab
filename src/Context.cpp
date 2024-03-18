#include "Graphics.hpp"
#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include <set>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Context.hpp"
#include "Listener.hpp"

namespace Context {

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

struct Frame {
  glm::vec2 center{0.0f, 0.0f};
  float scale{500.0f};
  float w = 1000.0f, h = 1000.0f;

  glm::mat4 world_to_graphics()
  {
    glm::mat4 m{1.0f};
    m = glm::scale(m, glm::vec3(w / scale / 2.0f, h / scale / 2.0f, 1.0f));
    m = glm::translate(m, glm::vec3(center, 0.0f));
    m = glm::inverse(m);
    return m;
  }

  glm::mat4 window_to_world()
  {
    glm::mat4 m{1.0f};
    m = glm::scale(m, glm::vec3{1.0f / scale * 1.25f, -1.0f / scale * 1.25f, 1.0f});
    m = glm::translate(m, glm::vec3{-w / 2.0f / 1.25f, -h / 2.0f / 1.25f, 0.0f});
    return m;
  }
} frame;

GLFWwindow* init()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,
                                          SCR_HEIGHT,
                                          "spline", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);

    glfwSetCursorPosCallback(window, cursor_position_callback);

    glfwSetKeyCallback(window, key_callback);

    return window;
}

std::vector<Listener*> listeners;
std::vector<Listener*> release_listeners;

void add_listener(Listener* listener)
{
  listeners.push_back(listener);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    frame.w = static_cast<float>(width);
    frame.h = static_cast<float>(height);
    Graphics::update_camera(frame.world_to_graphics());
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
  double xd = 0, yd = 0;
  glfwGetCursorPos(window, &xd, &yd);
  float x = static_cast<float>(xd);
  float y = static_cast<float>(yd);
  glm::vec4 world_position = frame.window_to_world() * glm::vec4{x, y, 1.0f, 1.0f};
  glm::vec4 test = frame.window_to_world() * glm::vec4{17.0f, -1.0f, 1.0f, 1.0f};
  glm::vec2 position{world_position.x, world_position.y};
  glm::vec2 testpos{test.x, test.y};
  if (action == GLFW_PRESS) {
    // std::cout << std::format("window size ({}, {})\n", frame.w, frame.h);
    // std::cout << std::format("screen ({}, {})\n", xd, yd);
    // std::cout << std::format("world ({}, {})\n", position.x, position.y);
    // std::cout << std::format("test ({}, {})\n", test.x, test.y);
    for (Listener* listener : listeners)
    {
      if (listener->mouse_button_pressed(button, position))
      {
        release_listeners.push_back(listener);
        break;
      }
    }
  }
  else if (action == GLFW_RELEASE) {
    std::vector<Listener*> remove;
    for (Listener* listener : release_listeners)
    {
      if (listener->mouse_button_released(button, position)){
        remove.push_back(listener);
      }
    }
    for (Listener* listener : remove)
    {
      std::erase(release_listeners, listener);
    }
  }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
  float x = static_cast<float>(xpos);
  float y = static_cast<float>(ypos);
  glm::vec4 world_position = frame.window_to_world() * glm::vec4{x, y, 1.0f, 1.0f};
  glm::vec2 position{world_position.x, world_position.y};
  for (Listener* listener : release_listeners)
  {
    listener->cursor_position_changed(position);
  }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
}

}
