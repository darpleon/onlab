#include "PHSpatialController.hpp"
#include "PHSpatialQuintic.hpp"

PHSpatialController::PHSpatialController(std::array<glm::vec3, 4> ctrl)
  : ctrl{ctrl}, ph{ctrl}, view{nullptr}, polygon{std::vector<glm::vec3>{ctrl.begin(), ctrl.end()}}
{
  view = Graphics::QuatBernsteinView{ph.curve()};
  Graphics::add_object(&polygon);
  Graphics::add_object(&view);
}


