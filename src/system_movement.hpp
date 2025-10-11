#pragma once

namespace ecs {

void ProcessRec(Entity& e) {
  e.movePos(*e.speed);
}

void ProcessEntityMovement(sf::RenderWindow& win, EntityMan& eman) {
  for (auto& e : eman.entities) {
    if (!e.speed) {
      continue;
    }

    if (e.shapeRec) {
      ProcessRec(e);
    } else if (e.shapeCir) {
      continue;
    } else if (e.shapeLine) {
      continue;
    }
  }
}

}  // namespace ecs
