#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

#include "utils.hpp"

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

  // "Move" a position for a shape
  void movePos(sf::Vector2f m) {
    if (shapeRec) {
      shapeRec->move(m);
      UpdateRecData();
    }
  }

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
    speed = {0.05f, 0.05f};
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

  // Marshal an Entity to a string
  std::string marshal() {
    std::string mStr = "";

    // Rectangle R G B POS_X POS_Y W H V_X V_Y
    if (shapeRec && speed) {
      mStr += fmt::format("{} ", "Rectangle");
      mStr += fmt::format("{} ", shapeRec->getFillColor().r);
      mStr += fmt::format("{} ", shapeRec->getFillColor().g);
      mStr += fmt::format("{} ", shapeRec->getFillColor().b);
      mStr += fmt::format("{} ", shapeRec->getPosition().x);
      mStr += fmt::format("{} ", shapeRec->getPosition().y);
      mStr += fmt::format("{} ", shapeRec->getSize().x);
      mStr += fmt::format("{} ", shapeRec->getSize().y);
      mStr += fmt::format("{} ", speed->x);
      mStr += fmt::format("{}", speed->y);
    }

    // Line R G B POS_X POS_Y POS_X POS_Y
    if (shapeLine) {
      mStr += fmt::format("{} ", "Line");
      mStr += fmt::format("{} ", (*shapeLine)[0].color.r);
      mStr += fmt::format("{} ", (*shapeLine)[0].color.g);
      mStr += fmt::format("{} ", (*shapeLine)[0].color.b);
      mStr += fmt::format("{} ", (*shapeLine)[0].position.x);
      mStr += fmt::format("{} ", (*shapeLine)[0].position.y);
      mStr += fmt::format("{} ", (*shapeLine)[1].position.x);
      mStr += fmt::format("{} ", (*shapeLine)[1].position.y);
    }

    return mStr;
  }

  std::string log() {
    std::string logString = "";
    if (shapeRec) {
      // Type : Val - Name : Val - centerPos : Val - Spd : Val - Player : Val
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Type");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", "Rectangle");
      logString += " - ";
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Name");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", name);
      logString += " - ";
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "topLeftPos");
      logString +=
          fmt::format(fg(VAL_COLOR), "{:<10}", printVector(recBounds[0]));
      logString += " - ";
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Spd");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", printVector(*speed));
      logString += " - ";
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Player");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", *player);
      return logString;
    }
    if (shapeLine) {
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Type");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", "Line");
      logString += " - ";
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Name");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", name);
      return logString;
    }
    return logString;
  }
};

class EntityMan {
 private:
 public:
  std::vector<Entity> entities{};
  void AddEntity(Entity e) { entities.push_back(e); }
};

}  // namespace ecs
