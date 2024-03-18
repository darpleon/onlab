#include "glad.h"
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <format>
#include <iostream>
#include "Graphics.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <optional>
#include "Shader.hpp"
namespace Graphics {
  
       // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
// unsigned int color_uniform;

std::optional<Shader> basic_shader;


glm::vec3 orange{6.f, 0.3f, 0.f};
glm::vec3 yellow{9.f, 0.8f, 0.f};
glm::vec3 green1{0.25f, 0.65f, 0.25f};
glm::vec3 green2{0.2f, 0.85f, 0.2f};
glm::vec3 brick{0.75f, 0.25f, 0.35f};
glm::vec3 gray{0.7f};
glm::vec3 white{0.85f};

void debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                    GLsizei length, const char* message, const void* userParam) {
    std::cout << message << "\n";
}

void init() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debug_callback, NULL);

    basic_shader = Shader("src/shader/basic.vert", "src/shader/basic.frag");
    basic_shader->use();
}

void update_camera(const glm::mat4& view_matrix)
{
  glUniformMatrix4fv(glGetUniformLocation(basic_shader->ID, "camera"),
                     1, GL_FALSE, glm::value_ptr(view_matrix)); 
}

GLObject::GLObject() : GLObject(GL_LINE_STRIP, orange, 5) {}

GLObject::GLObject(unsigned int mode, glm::vec3 color, unsigned int size) 
  : mode(mode), color(color), width(size) {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
}

void GLObject::setVertices(const std::vector<glm::vec2>& v) {
  vertices = v;
}

void GLObject::draw() {
  switch (mode) {
    case GL_LINES:
    case GL_LINE_STRIP:
      glLineWidth(width);
      break;
    case GL_POINTS:
      glPointSize(width);
      break;
  }
  basic_shader->setVec3("Color", color);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER,
               sizeof(glm::vec2) * vertices.size(),
               &vertices[0], GL_DYNAMIC_DRAW);
  glDrawArrays(mode, 0, vertices.size());
}

PolynomialView::PolynomialView(Polynomial<glm::vec2>* polynomial)
    : polynomial(polynomial), curve(GL_LINE_STRIP, orange, 5) {};

void PolynomialView::draw()
{
  float start = 0.0f, end = 1.0f;
  size_t res = 100;
  float step = (end - start) / static_cast<float>(res);
  std::vector<glm::vec2> verts{};
  verts.reserve(res + 1);
  for (float t = start; t < end; t += step)
  {
    glm::vec2 v = polynomial->evaluate(t);
    verts.push_back(v);
    // std::cout << std::format("{}|{}\n", v.x, v.y);
  }
  curve.setVertices(verts);
  curve.draw();
  // std::cout << "=============================\n";
}

BernsteinView::BernsteinView(Bernstein<glm::vec2>* bernstein)
    : bernstein(bernstein), curve(GL_LINE_STRIP, orange, 5),
                            c_points(GL_POINTS, brick, 10),
                            c_polygon(GL_LINE_STRIP, gray, 2)
{
}

void BernsteinView::draw()
{
  float start = 0.0f, end = 1.0f;
  size_t res = 100;
  float step = (end - start) / static_cast<float>(res);
  std::vector<glm::vec2> verts{};
  verts.reserve(res + 1);
  for (float t = start; t < end; t += step)
  {
    glm::vec2 v = bernstein->evaluate(t);
    verts.push_back(v);
    // std::cout << std::format("{}|{}\n", v.x, v.y);
  }
  std::vector<glm::vec2> ctrl = bernstein->control_points();
  c_polygon.setVertices(ctrl);
  c_polygon.draw();
  c_points.setVertices(ctrl);
  c_points.draw();
  curve.setVertices(verts);
  curve.draw();
  // std::cout << "=============================\n";
}

PHPlanarQuinticView::PHPlanarQuinticView(PHPlanarQuintic* ph)
    : ph(ph), curve(GL_LINE_STRIP, yellow, 5),
              offset(GL_LINE_STRIP, brick, 4),
              true_polygon{{}}
{
}

void PHPlanarQuinticView::draw()
{
  float start = 0.0f, end = 1.0f;
  size_t res = 100;
  float step = (end - start) / static_cast<float>(res);
  std::vector<glm::vec2> verts{};
  verts.reserve(res + 1);
  std::vector<glm::vec2> offset_verts{};
  offset_verts.reserve(res + 1);
  for (float t = start; t < end; t += step)
  {
    glm::vec2 c = ph->evaluate(t);
    verts.push_back(c);
    glm::vec2 o = ph->evaluate_offset(t, 0.2f);
    offset_verts.push_back(o);
    // std::cout << std::format("{}|{}\n", v.x, v.y);
  }
  curve.setVertices(verts);
  curve.draw();
  offset.setVertices(offset_verts);
  offset.draw();
  true_polygon.ctrl = ph->true_controls();
  true_polygon.draw();
  // std::cout << "=============================\n";
}

ControlPolygonView::ControlPolygonView(std::vector<glm::vec2> ctrl)
  : ctrl{ctrl}, points{GL_POINTS, brick, 10}, lines{GL_LINE_STRIP, gray, 2}
{
}

void ControlPolygonView::draw()
{
  lines.setVertices(ctrl);
  lines.draw();
  points.setVertices(ctrl);
  points.draw();
}

std::vector<Drawable*> objects;

void add_object(Drawable* d) {
  objects.push_back(d);
}

void draw() {

  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  for (Drawable* object: objects) {
    object->draw();
  }
}

}
