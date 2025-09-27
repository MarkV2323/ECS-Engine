#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

namespace ecs {
class Entity {
 private:
  sf::Vector2f recBounds[4];

 public:
  // Every entity has a name
  std::string name = "null";

  // Entity may only have 1 of these.
  std::optional<sf::RectangleShape> shapeRec = std::nullopt;
  std::optional<sf::CircleShape> shapeCir = std::nullopt;
  std::optional<sf::VertexArray> shapeLine = std::nullopt;
  std::optional<sf::Vector2f> speed = std::nullopt;

  void setName(std::string s) { name = s; }
  void setSpeed(sf::Vector2f v) { speed = v; }

  void setRec(sf::RectangleShape s) {
    shapeRec = s;
    shapeCir = std::nullopt;
    shapeLine = std::nullopt;
    speed = {0.005f, 0.005f};
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
  void addEntity(Entity e) { entities.push_back(e); }
};

}  // namespace ecs
