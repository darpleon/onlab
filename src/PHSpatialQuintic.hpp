#pragma once
#include "Bernstein.hpp"
#include "Polynomial.hpp"
#include <glm/ext/quaternion_float.hpp>
#include <glm/ext/vector_float3.hpp>

using quat = glm::quat;

class PHSpatialQuintic {
public:
  PHSpatialQuintic(std::array<glm::vec3, 4> controls);

  // PHPlanarQuintic(std::initializer_list<complex> controls);

  // std::vector<glm::vec3> true_controls();

  void set_controls(std::array<glm::vec3, 4> controls);

  Bernstein<quat>* curve();

  // glm::vec3 evaluate(float t);


private:
  // Bernstein<quat> bernstein;
  std::vector<Bernstein<quat>> curves{};

  // std::array<complex, 4> ctrl;
  // Polynomial<complex> polynomial;
  // Bernstein<complex> deriv;
  // Bernstein<float> sigma;
};
