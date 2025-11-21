#pragma once

#include "entity_manager.hpp"
namespace ecs {

inline void ProcessRec(Entity& e) { e.MovePos(*e.speed); }

inline void ProcessCir(Entity& e) { e.MovePos(*e.speed); }

inline void ProcessEntityMovement(sf::RenderWindow& win, EntityMan& eman) {
  for (auto& e : eman.entities) {
    if (!e.speed) {
      continue;
    }

    if (e.shapeRec) {
      ProcessRec(e);
    } else if (e.shapeCir) {
      ProcessCir(e);
    } else if (e.shapeLine) {
      continue;
    }
  }
}

}  // namespace ecs
