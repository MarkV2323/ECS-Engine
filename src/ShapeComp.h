#pragma once

#include <SFML/Graphics/CircleShape.hpp>

namespace ecse {
class ShapeComp {
 private:
  ShapeComp() {}

 public:
  sf::CircleShape shape{};

  ShapeComp(float r, int points, const sf::Color& fill,
            const sf::Color& outline, float thickness)
      : shape(r, points) {
    shape.setFillColor(fill);
    shape.setOutlineColor(outline);
    shape.setOutlineThickness(thickness);
    shape.setOrigin(r, r);
  }
  ~ShapeComp() {}
};
}  // namespace ecse