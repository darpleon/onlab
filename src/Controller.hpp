#pragma once

#include "Camera.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float2.hpp>

class Controller {
public:
  virtual bool key_pressed(int key, int mods)
  {
    return false;
  }

  virtual bool key_released(int key)
  {
    return false;
  }

  virtual bool mouse_button_pressed(int button, glm::vec2 position)
  {
    return false;
  }

  virtual bool mouse_button_released(int button, glm::vec2 position)
  {
    return false;
  }

  virtual bool cursor_position_changed(glm::vec2 position)
  {
    return false;
  }


private:
  // Camera& camera;
};
