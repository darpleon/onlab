#pragma once

#include "Controller.hpp"
#include "Graphics.hpp"
#include "PHSpatialQuintic.hpp"

class PHSpatialController : public Controller {
public:
  PHSpatialController(std::array<glm::vec3, 4> ctrl);

private:
  std::array<glm::vec3, 4> ctrl;
  PHSpatialQuintic ph;
  Graphics::QuatBernsteinView view; 
  Graphics::ControlPolygonView3D polygon;

};
