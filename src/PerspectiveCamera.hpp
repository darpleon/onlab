#pragma once

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/vector_float3.hpp>

class PerspectiveCamera {
public:
  glm::mat4 getMatrix();
  void setAspect(float a);
  void rotate(float angle);

private:
  glm::vec3 pos{0.0f, 0.0f, -2.0f};
  glm::vec3 lookAt{0.0f, 0.0f, 0.0f};
  float aspect = 1.0f;

  glm::vec3 up{0.0f, 1.0f, 0.0f};
};
