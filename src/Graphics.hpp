#pragma once
// #include "BSpline.hpp"
#include "Bernstein.hpp"
#include "PHPlanarQuintic.hpp"
#include "Polynomial.hpp"
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>
#include <complex>

using complex = std::complex<float>;

namespace Graphics {

  void init();

  void draw();

  void update_camera(const glm::mat4& view_matrix);

  
  class Drawable {
  public:
    virtual void draw() = 0;
  };

  class GLObject : Drawable {
    unsigned int VAO, VBO;
    std::vector<glm::vec2> vertices;
    unsigned int mode;
    unsigned int width;
    glm::vec3 color;

  public:
    GLObject();
    GLObject(unsigned int mode, glm::vec3 color, unsigned int size);
    void draw() override;
    void setVertices(const std::vector<glm::vec2>& v);
  };  

  class PolynomialView : public Drawable {
    GLObject curve;
    Polynomial<glm::vec2>* polynomial;
  
  public:
    PolynomialView(Polynomial<glm::vec2>* polynomial);
    void draw() override;
  };


  class BernsteinView : public Drawable {
    GLObject curve;
    GLObject c_points;
    GLObject c_polygon;
    Bernstein<glm::vec2>* bernstein;
  
  public:
    BernsteinView(Bernstein<glm::vec2>* bernstein);
    void draw() override;
  };

  class ControlPolygonView : public Drawable {
  public:
    ControlPolygonView(std::vector<glm::vec2> ctrl);
    void draw() override;

    std::vector<glm::vec2> ctrl;
  private:
    GLObject points;
    GLObject lines;
  };

  class PHPlanarQuinticView : public Drawable {
    GLObject curve;
    GLObject offset;
    ControlPolygonView true_polygon;
    PHPlanarQuintic* ph;

  public:
    PHPlanarQuinticView(PHPlanarQuintic* ph);
    void draw() override;
  };

  void add_object(Drawable* d);
}
