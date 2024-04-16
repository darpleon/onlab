#include "PHSpatialQuintic.hpp"
#include <glm/geometric.hpp>
#include <complex>

using complex = std::complex<float>;

float trp(glm::vec3 a, glm::vec3 b, glm::vec3 c)
{
  return glm::dot(glm::cross(a, b), c);
}

std::array<complex, 4> solve_quartic(std::array<float, 5> f)
{
  std::array<complex, 4> roots{};

  complex A = f[4], B = f[3], C = f[2], D = f[1], E = f[0];

  complex a = (-3.0f * pow(B, 2.0f)) / (8.0f * pow(A, 2.0f)) + C / A;
  complex b = pow(B, 3.0f) / (8.0f * pow(A, 3.0f)) - (B * C) / (2.0f * pow(A, 2.0f)) + D / A;
  complex c = (-3.0f * pow(B, 4.0f)) / (256.0f * pow(A, 4.0f)) + (C * pow(B, 2.0f)) / (16.0f * pow(A, 3.0f))
              - (B * D) / (4.0f * pow(A, 2.0f)) + E / A;

  complex m = -B / (4.0f * A);

  if (std::abs(b) < 0.0001f) {
    complex d = sqrt(pow(a, 2.0f) - 4.0f * c);
    complex r1 = sqrt(0.5f * (-a + d));
    complex r2 = sqrt(0.5f * (-a - d));

    roots[0] = m + r1;
    roots[1] = m + r2;
    roots[2] = m - r1;
    roots[3] = m - r2;

    return roots;
  }

  complex P = -pow(a, 2.0f) / 12.0f - c;
  complex Q = -pow(a, 3.0f) / 108.0f + (a * c) / 3.0f - pow(b, 2.0f) / 8.0f;
  complex R = -Q / 2.0f + sqrt(pow(Q, 2.0f) / 4.0f + pow(P, 3.0f) / 27.0f);
  complex U = pow(R, 1.0f / 3.0f);

  complex V;
  if (std::abs(U) < 0.0001f) {
    V = -pow(Q, 1.0f / 3.0f);
  }
  else {
    V = U - P / (3.0f * U);
  }
  complex y = (-5.0f * a) / 6.0f + V;
  complex W = sqrt(a + 2.0f * y);

  complex s1 = sqrt(-(3.0f * a + 2.0f * y + (2.0f * b) / W));
  complex s2 = sqrt(-(3.0f * a + 2.0f * y - (2.0f * b) / W));

  roots[0] = m + 0.5f * (W + s1);
  roots[1] = m + 0.5f * (W - s1);
  roots[2] = m + 0.5f * (-W + s2);
  roots[3] = m + 0.5f * (-W - s2);

  return roots;
}

void PHSpatialQuintic::set_controls(std::array<glm::vec3, 4> controls)
{
  // glm::vec3 di{1.0f, 0.0f, 1.0f};
  // glm::vec3 df{0.0f, 1.0f, 1.0f};
  glm::vec3 di = 3.0f * (controls[1] - controls[0]);
  glm::vec3 df = 3.0f * (controls[3] - controls[2]);
  glm::vec3 ri = glm::normalize(di);
  glm::vec3 rf = glm::normalize(df);
  float mi = glm::length(di);
  float mf = glm::length(df);
  // glm::vec3 pi{0.0f, 0.0f, 0.0f};
  // glm::vec3 pd{1.0f, 1.0f, 1.0f};
  glm::vec3 pi = controls[0];
  glm::vec3 pd = controls[3] - controls[0];
  glm::vec3 h = 120.0f * pd - 15.0f * (di + df);

  float lai = (1.0f + ri.x);
  float laf = (1.0f + rf.x);
  float denom = sqrtf(lai * laf);

  glm::vec3 u{};
  u.x = lai * laf - (ri.y * rf.y + ri.z * rf.z);
  u.y = laf * ri.y + lai * rf.y;
  u.z = laf * ri.z + lai * rf.z;
  u *= sqrtf(mi * mf) / denom;

  std::cout << std::format("u: {}, {}, {}\n", u.x, u.y, u.z);

  glm::vec3 v{};
  v.x = -(ri.y * rf.z - rf.y * ri.z);
  v.y = lai * rf.z - laf * ri.z;
  v.z = laf * ri.y - lai * rf.y;
  v *= sqrtf(mi * mf) / denom;

  std::cout << std::format("v: {}, {}, {}\n", v.x, v.y, v.z);

  std::array<float, 5> d{};
  d[4] = trp(h, df, u) * trp(di, h, u) - trp(di, df, h - 5.0f * u) * trp(di, df, h - 5.0f * u);
  d[3] = -2.0f * trp(h, df, u) * trp(di, h, v) - 2.0f * trp(di, h, u) * trp(h, df, v)
          - 20.0f * trp(di, df, v) * trp(di, df, h - 5.0f * u);
  d[2] = -2.0f * trp(h, df, u) * trp(di, h, u) + 4.0f * trp(h, df, v) * trp(di, h, v)
          - 100.0f * trp(di, df, v) * trp(di, df, v) - 2.0f * trp(di, df, h - 5.0f * u) * trp(di, df, h + 5.0f * u);
  d[1] = 2.0f * trp(h, df, v) * trp(di, h, u) + 2.0f * trp(di, h, v) * trp(h, df, u)
          - 20.0f * trp(di,df, v) * trp(di, df, h + 5.0f * u);
  d[0] = trp(h, df, u) * trp(di, h, u) - trp(di, df, h + 5.0f * u) * trp(di, df, h + 5.0f * u);

  std::cout << "coeffs:\n";
  for (float cf : d) {
    std::cout << cf << "\n";
  }

  std::array<float, 5> dd{1.34494f, 21.2969f, -23.6064f, -18.2516f, 1.0f};

  std::array<complex, 4> roots = solve_quartic(d);

  std::vector<std::array<quat, 3>> A012{};

  for (complex root : roots) {
    if (std::abs(root.imag()) > 0.001f) {
      continue;
    }
    float t = root.real();
    std::cout << std::format("t: {}\n", t);
    float cph = (1.0f - t * t) / (1.0f + t * t);
    float sph = (2.0f * t) / (1.0f + t * t);
    glm::vec3 uv = u * cph + v * sph;
    float div = trp(di, df, uv);
    float sq0 = trp(h, df, uv) / div;
    float sq2 = trp(di, h, uv) / div;

    // std::cout << std::format("16k0^2: {}, 16k2^2: {}\n", sq0, sq2);

    if (sq0 < 0.0f || sq2 < 0.0f) {
      continue;
    }

    std::cout << std::format("phi: {}\n", acosf(cph));

    float comp = trp(di, df, h) / div;

    float k0 = sqrtf(sq0) / 4.0f;
    float k2 = sqrtf(sq2) / 4.0f;

    if (std::abs(16.0f * k0 * k2 - 5.0f - comp) > 0.001f) {
      k2 *= -1.0f;
      if (std::abs(16.0f * k0 * k2 - 5.0f - comp) > 0.001f) {
        std::cout << "this shouldn't happen\n";
      }
    }

    std::cout << std::format("k0: {}| k2: {}\n", k0, k2);
    
    float a0 = k0 - 3.0f / 4.0f;
    float b0 = -k0 - 3.0f / 4.0f;
    float a2 = k2 - 3.0f / 4.0f;
    float b2 = -k2 - 3.0f / 4.0f;

    float phi0 = 0;
    float phi2 = 2.0f * atanf(t);

    quat A0 = quat{-sinf(phi0), cosf(phi0),
                    (ri.y * cosf(phi0) + ri.z * sinf(phi0)) / lai,
                    (ri.z * cosf(phi0) - ri.y * sinf(phi0)) / lai}
                      * sqrtf(0.5f * lai * mi);
    quat A2 = quat{-sinf(phi2), cosf(phi2),
                    (rf.y * cosf(phi2) + rf.z * sinf(phi2)) / laf,
                    (rf.z * cosf(phi2) - rf.y * sinf(phi2)) / laf}
                      * sqrtf(0.5f * laf * mf);

    A012.emplace_back(std::array<quat, 3>{A0, a0 * A0 + a2 * A2, A2});
    A012.emplace_back(std::array<quat, 3>{A0, b0 * A0 + b2 * A2, A2});
  }

  curves.clear();

  quat i{0.0f, 1.0f, 0.0f, 0.0f};

  for (auto& [A0, A1, A2] : A012) {
    quat A0c = glm::conjugate(A0);
    quat A1c = glm::conjugate(A1);
    quat A2c = glm::conjugate(A2);
    std::vector<quat> p{6};
    p[0] = quat{0.0f, pi.x, pi.y, pi.z};
    p[1] = p[0] + 0.2f * A0 * i * A0c;
    p[2] = p[1] + 0.1f * (A0 * i * A1c + A1 * i * A0c);
    p[3] = p[2] + 1.0f / 30.0f * (A0 * i * A2c + 4.0f * A1 * i * A1c + A2 * i * A0c);
    p[4] = p[3] + 0.1f * (A1 * i * A2c + A2 * i * A1c);
    p[5] = p[4] + 0.2f * A2 * i * A2c;


    curves.emplace_back(p);
  }

}

PHSpatialQuintic::PHSpatialQuintic(std::array<glm::vec3, 4> controls)
{
  set_controls(controls);
}

Bernstein<quat>* PHSpatialQuintic::curve()
{
  return &curves[0];
}
