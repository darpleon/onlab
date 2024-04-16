#pragma once

#include "Graphics.hpp"
#include "Controller.hpp"
#include "PHPlanarQuintic.hpp"

class PHDemo : public Controller, public Graphics::Drawable{
public:
  PHDemo(std::array<glm::vec2, 4> ctrl);

  virtual void draw() override;

  virtual bool mouse_button_pressed(int button, glm::vec2 position) override;

  virtual bool mouse_button_released(int button, glm::vec2 position) override;

  virtual bool cursor_position_changed(glm::vec2 position) override;


private:
  std::array<glm::vec2, 4> ctrl;
  PHPlanarQuintic ph;
  Graphics::PHPlanarQuinticView view;
  Graphics::ControlPolygonView c_polygon;
  std::optional<size_t> selected_idx{};
  // Bernstein<glm::vec2> bs;
};
