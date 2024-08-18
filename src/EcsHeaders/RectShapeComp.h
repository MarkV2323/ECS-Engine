#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

namespace ecse {
class RectShapeComp {
 private:
  RectShapeComp() {}

 public:
  sf::RectangleShape shape{};

  RectShapeComp(float x, float y, int points, const sf::Color& fill,
                const sf::Color& outline, float thickness)
      : shape(sf::Vector2f(x, y)) {
    shape.setFillColor(fill);
    shape.setOutlineColor(outline);
    shape.setOutlineThickness(thickness);
    shape.setOrigin(sf::Vector2f(x, y));
  }
  ~RectShapeComp() {}
};
}  // namespace ecse