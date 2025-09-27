#pragma once

#include "entity_manager.hpp"
#include "utils.hpp"

namespace ecs {

void follow_cursor(sf::RenderWindow& win, EntityMan& eman) {
  // Pass an entity and update it's position based on the
  // cursor position
  sf::Vector2f cursor = static_cast<sf::Vector2f>(sf::Mouse::getPosition(win));
  for (auto& e : eman.entities) {
    if (!e.player) continue;

    if (e.shapeRec) {
      sf::Vector2f diff = {e.recSize.x / 2, e.recSize.y / 2};
      sf::Vector2f cursorDiffed = cursor - diff;
      e.setPos(cursorDiffed);
    } else if (e.shapeCir) {
      continue;
    } else if (e.shapeLine) {
      continue;
    }
  }
}

}  // namespace ecs
