#include "PHDemo.hpp"

PHDemo::PHDemo(std::array<glm::vec2, 4> ctrl)
  : ctrl{ctrl}, ph{ctrl}, view{&ph},
    c_polygon{std::vector<glm::vec2>{ctrl.begin(), ctrl.end()}}
{
  Graphics::add_object(&c_polygon);
  Graphics::add_object(&view);
}

void PHDemo::draw()
{
  view.draw();
}

bool PHDemo::mouse_button_pressed(int button, glm::vec2 position)
{
  for (size_t i = 0; i < 4; i++)
  {
    if (glm::distance(ctrl[i], position) < 0.1)
    {
      selected_idx = i;
      return true;
    }
  }
  return false;
}

bool PHDemo::mouse_button_released(int button, glm::vec2 position)
{
  selected_idx.reset();
  return true;
}

bool PHDemo::cursor_position_changed(glm::vec2 position)
{
  if (selected_idx.has_value())
  {
    ctrl[selected_idx.value()] = position;
    c_polygon.ctrl[selected_idx.value()] = position;
    ph.set_controls(ctrl);
    return true;
  }
  return false;
}
