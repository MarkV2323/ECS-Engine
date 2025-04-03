#pragma once

#include <SFML/Graphics/CircleShape.hpp>

namespace ecse {
class CircleShape {
 private:
  CircleShape() {}

 public:
  sf::CircleShape shape{};

  CircleShape(float radius, int shape_points, sf::Color fill_color,
              sf::Color outline_color, float outline_thickness)
      : shape(radius, shape_points) {
    shape.setFillColor(fill_color);
    shape.setOutlineColor(outline_color);
    shape.setOutlineThickness(outline_thickness);
    shape.setOrigin(radius, radius);
  }
  ~CircleShape() {}
};
}  // namespace ecse