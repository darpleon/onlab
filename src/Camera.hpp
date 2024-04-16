#pragma once

#include <glm/ext/matrix_float4x4.hpp>
class Camera {
public:
  virtual glm::mat4 getMatrix() = 0;

  virtual void setAspect(float a) = 0;
};

class CameraBase : public Camera {
public:
  CameraBase(glm::vec3 pos = glm::vec3{0.0f, 0.0f, -5.0f},
	     glm::vec3 lookAt = glm::vec3{},
	     glm::vec3 up = glm::vec3{0.0f, 1.0f, 0.0f})
	      : pos(pos), lookAt(lookAt), up(up)
  {
  }

  virtual void setAspect(float a) override
  {
    aspect = a;
  }

protected:
  glm::vec3 pos;
  glm::vec3 lookAt;
  glm::vec3 up;

  float aspect = 1.0f;
};
