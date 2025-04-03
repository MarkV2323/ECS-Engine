#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

namespace ecse {
class RectangleShape {
 private:
  RectangleShape() {}

 public:
  sf::RectangleShape shape{};

  RectangleShape(float size_x, float size_y, sf::Color fill_color,
                 sf::Color outline_color, float outline_thickness)
      : shape(sf::Vector2f(size_x, size_y)) {
    shape.setFillColor(fill_color);
    shape.setOutlineColor(outline_color);
    shape.setOutlineThickness(outline_thickness);
    shape.setPosition(sf::Vector2f(0, 0));
  }
  ~RectangleShape() {}
};
}  // namespace ecse