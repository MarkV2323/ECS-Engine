#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

namespace ecs {
class Entity {
 private:
  void UpdateRecData() {
    if (!shapeRec) return;
    auto gb = shapeRec->getGlobalBounds().position;
    auto gbs = shapeRec->getGlobalBounds().size;
    recBounds[0] = gb;
    recBounds[1] = gb + sf::Vector2f(gbs.x, 0);
    recBounds[2] = gb + sf::Vector2f(0, gbs.y);
    recBounds[3] = gb + gbs;
    recCenter = {gb.x + (gbs.x / 2), gb.y + (gbs.y / 2)};
    recSize = gbs;
  }

 public:
  std::string name = "null";
  std::optional<sf::RectangleShape> shapeRec = std::nullopt;
  std::optional<sf::CircleShape> shapeCir = std::nullopt;
  std::optional<sf::VertexArray> shapeLine = std::nullopt;
  std::optional<sf::Vector2f> speed = std::nullopt;
  std::optional<bool> player = std::nullopt;

  // These are stored window "global" positions for the rectangle.
  sf::Vector2f recCenter{0, 0};
  sf::Vector2f recSize{0, 0};
  sf::Vector2f recBounds[4];

  // "Set" a position for a shape
  void setPos(sf::Vector2f p) {
    if (shapeRec) {
      shapeRec->setPosition(p);
      UpdateRecData();
    }
  }

  void setName(std::string s) { name = s; }
  void setSpeed(sf::Vector2f v) { speed = v; }
  void setPlayer() { player = true; }

  void setRec(sf::RectangleShape s) {
    shapeRec = s;
    shapeCir = std::nullopt;
    shapeLine = std::nullopt;
    speed = {0.005f, 0.005f};
    UpdateRecData();
  }

  void setCir(sf::CircleShape s) {
    shapeRec = std::nullopt;
    shapeCir = s;
    shapeLine = std::nullopt;
    speed = {0.005f, 0.005f};
  }

  void setLine(sf::VertexArray l) {
    shapeRec = std::nullopt;
    shapeCir = std::nullopt;
    shapeLine = l;
    speed = std::nullopt;
  }
};

class EntityMan {
 private:
 public:
  std::vector<Entity> entities{};
  void AddEntity(Entity e) { entities.push_back(e); }
};

}  // namespace ecs
