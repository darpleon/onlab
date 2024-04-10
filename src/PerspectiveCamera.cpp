#include "PerspectiveCamera.hpp"
#include <format>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>

glm::mat4 PerspectiveCamera::getMatrix() {
  return glm::perspective(fovY, aspect, nearZ, farZ) * glm::lookAt(pos, lookAt, up);
}

void PerspectiveCamera::rotate(float angle, glm::vec3 axis) {
  glm::vec4 pos4 = glm::vec4{pos.x, pos.y, pos.z, 1.0f};
  pos4 = pos4 * glm::rotate(glm::mat4{1.0f}, angle, axis);
  pos = glm::vec3{pos4};
}

  bool PerspectiveCamera::mouse_button_pressed(int button, glm::vec2 position)
  {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
      dragging = true;
      previous_position = position;
      return true;
    }
    else {
      return false;
    }
  }

  bool PerspectiveCamera::mouse_button_released(int button, glm::vec2 position)
  {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
      dragging = false;
      return true;
    }
    else {
      return false;
    }
  }

  bool PerspectiveCamera::cursor_position_changed(glm::vec2 position)
  {
    if (dragging) {
      glm::vec2 diff = position - previous_position;
      rotate(diff.x * 0.01f, up);
      glm::vec3 axis = glm::normalize(glm::cross(lookAt - pos, up));
      rotate(diff.y * 0.01f, axis);
      previous_position = position;
      return true;
    }
    else {
      return false;
    }
  }

