#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

namespace ecse {
class RectShapeComp {
 private:
  RectShapeComp() {}

 public:
  sf::RectangleShape shape{};

  RectShapeComp(float size_x, float size_y, int points, const sf::Color& fill,
                const sf::Color& outline, float thickness)
      : shape(sf::Vector2f(size_x, size_y)) {
    shape.setFillColor(fill);
    shape.setOutlineColor(outline);
    shape.setOutlineThickness(thickness);
    shape.setPosition(sf::Vector2f(0, 0));
  }
  ~RectShapeComp() {}
};
}  // namespace ecse