#pragma once
#include "Bernstein.hpp"
#include "Polynomial.hpp"
#include <complex>
#include <glm/ext/vector_float2.hpp>

using complex = std::complex<float>;

class PHPlanarQuintic {
public:
  PHPlanarQuintic(std::array<glm::vec2, 4> controls);
  // PHPlanarQuintic(std::initializer_list<complex> controls);

  std::vector<glm::vec2> true_controls();

  void set_controls(std::array<glm::vec2, 4> controls);

  glm::vec2 evaluate(float t);

  glm::vec2 evaluate_offset(float t, float d);

private:
  // std::array<complex, 4> ctrl;
  // Polynomial<complex> polynomial;
  Bernstein<complex> bernstein;
  Bernstein<complex> deriv;
  Bernstein<float> sigma;
  // Polynomial<float> u;
  // Polynomial<float> v;
  // void calculate_hermite(complex d0, complex d1);
};
