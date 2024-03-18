#include "PHPlanarQuintic.hpp"
#include <array>
#include <cstdlib>
#include <glm/ext/vector_float2.hpp>

using namespace std::complex_literals;

std::array<complex, 3> calculate_abkr(complex d0, complex d1);

PHPlanarQuintic::PHPlanarQuintic(std::array<glm::vec2, 4> controls)
{
  set_controls(controls);
}
 
void PHPlanarQuintic::set_controls(std::array<glm::vec2, 4> controls)
{
  // std::cout << "set_controls\n";
  std::array<complex, 4> ctrl;
  for (size_t i = 0; i < 4; i++)
  {
    ctrl[i] = {controls[i].x , controls[i].y};
  }
  ctrl[1] = 3.0f * (ctrl[1] - ctrl[0]);
  ctrl[2] = 3.0f * (ctrl[3] - ctrl[2]);
  complex d0 = ctrl[1] / (ctrl[3] - ctrl[0]);
  complex d1 = ctrl[2] / (ctrl[3] - ctrl[0]);
  auto [a, b, kr] = calculate_abkr(d0, d1);
  complex w0 = kr * a * b;
  complex w1 = -kr * 0.5f * (a * (1.0f - b) + (1.0f - a) * b);
  complex w2 = kr * (1.0f - a) * (1.0f - b);
  Bernstein<complex> w{w0, w1, w2};
  // std::cout << "created w\n";
  std::vector<float> u_ctrl;
  std::vector<float> v_ctrl;
  for (complex c : w.control_points())
  {
    u_ctrl.push_back(c.real());
    v_ctrl.push_back(c.imag());
  }
  Bernstein<float> u{u_ctrl};
  Bernstein<float> v{v_ctrl};
  sigma = u * u + v * v;
  sigma = sigma * std::abs(ctrl[3] - ctrl[0]);
  deriv = w * w;
  deriv = deriv * (ctrl[3] - ctrl[0]);
  // std::cout << "squared w\n";
  bernstein = deriv.integral();
  bernstein = bernstein - bernstein.evaluate(0.0f);
  bernstein = bernstein + ctrl[0];

  // Polynomial<complex> wp = Polynomial<complex>{-a, 1.0f} * Polynomial<complex>{-b, 1.0f} * kr;
  // Polynomial<complex> derivp = wp * wp;
  // polynomial = derivp.integral();
  // polynomial = polynomial - polynomial.evaluate(0.0f);
  // polynomial = polynomial * (ctrl[3] - ctrl[0]);
  // polynomial = polynomial + ctrl[0];
}

std::vector<glm::vec2> PHPlanarQuintic::true_controls()
{
  std::vector<glm::vec2> controls;
  controls.reserve(bernstein.control_points().size());
  for (complex c : bernstein.control_points())
  {
    controls.push_back(glm::vec2{c.real(), c.imag()});
  }
  return controls;
}

glm::vec2 PHPlanarQuintic::evaluate(float t)
{
  complex value = bernstein.evaluate(t);
  return glm::vec2{std::real(value), std::imag(value)};
}

glm::vec2 PHPlanarQuintic::evaluate_offset(float t, float d)
{
  complex rc = bernstein.evaluate(t);
  glm::vec2 r{rc.real(), rc.imag()};
  complex nc = deriv.evaluate(t) * 1.0if / sigma.evaluate(t);
  glm::vec2 n{nc.real(), nc.imag()};
  return r + d * n;
}

std::array<complex, 2> solve_quadratic(std::array<complex, 3> coeffs)
{
  complex m = - coeffs[1] / (2.0f * coeffs[2]);
  complex p = coeffs[0] / coeffs[2];
  complex rad = sqrt(m * m - p);
  return {m + rad, m - rad};
}

std::array<complex, 3> calculate_abkr(complex d0, complex d1)
{
  complex ro0 = sqrt(d0 / d1);
  complex ro1 = -ro0;

  std::array<complex, 3> coeffs0 = {6.0f * ro0 * ro0 + 2.0f * ro0 + 6.0f - 30.f / d1, -3.0f * (1.0f + ro0), 1.0f};
  std::array<complex, 3> coeffs1 = {6.0f * ro1 * ro1 + 2.0f * ro1 + 6.0f - 30.f / d1, -3.0f * (1.0f + ro1), 1.0f};
  
  std::array<complex, 2> alpha0 = solve_quadratic(coeffs0);
  std::array<complex, 2> alpha1 = solve_quadratic(coeffs1);

  std::array<complex, 4> alpha = {alpha0[0], alpha0[1], alpha1[0], alpha1[1]};

  std::array<complex, 4> a_a;
  std::array<complex, 4> b_a;
  size_t candidate_index = 0;
  float candidate_distance = 0.0f;
  for (size_t i = 0; i < 4; i++)
  {
    std::array<complex, 3> m_coeffs = {i < 2 ? ro0 : ro1, - alpha[i], 1};
    std::array<complex, 2> mu = solve_quadratic(m_coeffs);
    a_a[i] = mu[0] / (mu[0] + 1.0f);
    b_a[i] = mu[1] / (mu[1] + 1.0f);
    float aim = std::imag(a_a[i]);
    float bim = std::imag(b_a[i]);
    if (aim * bim < 0.0f)
    {
      float distance = std::min(std::abs(aim), std::abs(bim));
      if (distance > candidate_distance)
      {
        candidate_index = i;
        candidate_distance = distance;
      }
    }
  }
  complex a = a_a[candidate_index];
  complex b = b_a[candidate_index];
  complex kr = sqrt(d0) / (a * b);
  return {a, b, kr};
}

