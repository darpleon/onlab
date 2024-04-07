#include "PerspectiveCamera.hpp"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>

glm::mat4 PerspectiveCamera::getMatrix() {
  return glm::infinitePerspective(1.0f, aspect, 0.1f) * glm::lookAt(pos, lookAt, up);
  // return glm::lookAt(pos, lookAt, up);
}

void PerspectiveCamera::rotate(float angle) {
  glm::vec4 pos4 = glm::vec4{pos.x, pos.y, pos.z, 1.0f};
  pos4 = pos4 * glm::rotate(glm::mat4{1.0f}, angle, up);
  pos = glm::vec3{pos4};
}

// void PerspectiveCamera::setAspect(float a) {
//   aspect = a;
// }
