#pragma once
// #include "BSpline.hpp"
#include "Bernstein.hpp"
#include "PHPlanarQuintic.hpp"
#include "PHSpatialQuintic.hpp"
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

  class GLObject3D : Drawable {
    unsigned int VAO, VBO;
    std::vector<glm::vec3> vertices;
    unsigned int mode;
    unsigned int width;
    glm::vec3 color;

  public:
    GLObject3D();
    GLObject3D(unsigned int mode, glm::vec3 color, unsigned int size);
    void draw() override;
    void setVertices(const std::vector<glm::vec3>& v);
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

  class ControlPolygonView3D : public Drawable {
  public:
    ControlPolygonView3D(std::vector<glm::vec3> ctrl);
    void draw() override;

    std::vector<glm::vec3> ctrl;
  private:
    GLObject3D points;
    GLObject3D lines;
  };

  class QuatBernsteinView : public Drawable {
    GLObject3D curve;
    GLObject3D c_points;
    GLObject3D c_polygon;
    Bernstein<quat>* bernstein;
  
  public:
    QuatBernsteinView(Bernstein<quat>* bernstein);
    void draw() override;
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

  class AxisView : public Drawable {
    GLObject3D xAxis, yAxis, zAxis;
  public:
    AxisView();
    void draw() override;
  };

  void add_object(Drawable* d);
}
