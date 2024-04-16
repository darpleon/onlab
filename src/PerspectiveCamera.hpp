#pragma once

#include "Camera.hpp"
#include "Controller.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

class PerspectiveCamera : public CameraBase, public Controller {
public:
  virtual glm::mat4 getMatrix() override;
  void rotate(float angle, glm::vec3 axis);

  virtual bool mouse_button_pressed(int button, glm::vec2 position) override;

  virtual bool mouse_button_released(int button, glm::vec2 position) override;

  virtual bool cursor_position_changed(glm::vec2 position) override;

private:
  float fovY = M_PIf / 2.0f;
  float nearZ = 0.1f;
  float farZ = 10.0f;

  bool dragging = false;
  glm::vec2 previous_position{};
};
