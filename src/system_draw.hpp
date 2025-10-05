#pragma once

#include <SFML/Graphics.hpp>

#include "entity_manager.hpp"

namespace ecs {

// Draw all possible entities from the EntityManager
void DrawEman(sf::RenderWindow& win, EntityMan& eman) {
  win.clear();
  for (auto& e : eman.entities) {
    if (e.shapeRec) win.draw(*e.shapeRec);
    if (e.shapeCir) win.draw(*e.shapeCir);
    if (e.shapeLine) win.draw(*e.shapeLine);
  }
  win.display();
}

}  // namespace ecs
