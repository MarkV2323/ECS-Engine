#pragma once

#include "entity_manager.hpp"
#include "utils.hpp"

namespace ecs {

inline void ProcessAnimations(EntityMan& eman) {
  for (auto& e : eman.entities) {
    if (!e.animations) continue;
    if (!e.shapeSprite) continue;
    if (e.ld == Entity::none) continue;
    std::string logStr{};

    e.gameFrame++;
    e.animFrame = (e.gameFrame / 10) % e.frameCount;

    auto tr = e.shapeSprite->getTextureRect();
    sf::Vector2i topLeftPos{};
    topLeftPos.x = e.animFrame * tr.size.x;
    topLeftPos.y = tr.position.y;
    e.shapeSprite->setTextureRect({topLeftPos, tr.size});
  }
}

}  // namespace ecs
