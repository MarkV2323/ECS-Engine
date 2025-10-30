#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdint>
#include <sstream>
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

    // Name Rectangle R G B POS_X POS_Y W H V_X V_Y player
    if (shapeRec && speed) {
      mStr += fmt::format("{} ", name);
      mStr += fmt::format("{} ", "Rectangle");
      mStr += fmt::format("{} ", shapeRec->getFillColor().r);
      mStr += fmt::format("{} ", shapeRec->getFillColor().g);
      mStr += fmt::format("{} ", shapeRec->getFillColor().b);
      mStr += fmt::format("{} ", shapeRec->getPosition().x);
      mStr += fmt::format("{} ", shapeRec->getPosition().y);
      mStr += fmt::format("{} ", shapeRec->getSize().x);
      mStr += fmt::format("{} ", shapeRec->getSize().y);
      mStr += fmt::format("{} ", speed->x);
      mStr += fmt::format("{} ", speed->y);
      if (player) {
        mStr += fmt::format("{}", (*player));
      } else {
        mStr += fmt::format("{}", false);
      }
    }

    // Name Line R G B POS_X POS_Y POS_X POS_Y player
    if (shapeLine) {
      mStr += fmt::format("{} ", name);
      mStr += fmt::format("{} ", "Line");
      mStr += fmt::format("{} ", (*shapeLine)[0].color.r);
      mStr += fmt::format("{} ", (*shapeLine)[0].color.g);
      mStr += fmt::format("{} ", (*shapeLine)[0].color.b);
      mStr += fmt::format("{} ", (*shapeLine)[0].position.x);
      mStr += fmt::format("{} ", (*shapeLine)[0].position.y);
      mStr += fmt::format("{} ", (*shapeLine)[1].position.x);
      mStr += fmt::format("{} ", (*shapeLine)[1].position.y);
      if (player) {
        mStr += fmt::format("{}", (*player));
      } else {
        mStr += fmt::format("{}", false);
      }
    }

    return mStr;
  }

  bool unmarshal(std::string s) {
    std::stringstream ss(s);
    std::string token;

    // Get name
    ss >> token;
    name = token;

    // Get type
    ss >> token;
    if (token == "Rectangle") {
      // build color
      uint8_t colorVal = 0;
      sf::Color color(0, 0, 0);
      ss >> token;
      colorVal = static_cast<uint8_t>(stoi(token));
      color.r = colorVal;
      ss >> token;
      colorVal = static_cast<uint8_t>(stoi(token));
      color.g = colorVal;
      ss >> token;
      colorVal = static_cast<uint8_t>(stoi(token));
      color.b = colorVal;

      // build pos
      sf::Vector2f pos;
      ss >> token;
      pos.x = static_cast<float>(stoi(token));
      ss >> token;
      pos.y = static_cast<float>(stoi(token));

      // build size
      sf::Vector2f size;
      ss >> token;
      size.x = static_cast<float>(stoi(token));
      ss >> token;
      size.y = static_cast<float>(stoi(token));

      // build speed
      sf::Vector2f spd;
      ss >> token;
      spd.x = static_cast<float>(stoi(token));
      ss >> token;
      spd.y = static_cast<float>(stoi(token));

      // build player
      ss >> token;
      if (token == "true") player = true;
      if (token == "false") player = false;

      // build rectangleShape
      auto recShape = buildRec(color, size, pos);

      // set rectangleShape
      setRec(recShape);

      // set speed
      speed = spd;

      return true;
    } else if (token == "Line") {
      // build color
      uint8_t colorVal = 0;
      sf::Color color(0, 0, 0);
      ss >> token;
      colorVal = static_cast<uint8_t>(stoi(token));
      color.r = colorVal;
      ss >> token;
      colorVal = static_cast<uint8_t>(stoi(token));
      color.g = colorVal;
      ss >> token;
      colorVal = static_cast<uint8_t>(stoi(token));
      color.b = colorVal;

      // build pos1
      sf::Vector2f pos1;
      ss >> token;
      pos1.x = static_cast<float>(stoi(token));
      ss >> token;
      pos1.y = static_cast<float>(stoi(token));

      // build pos2
      sf::Vector2f pos2;
      ss >> token;
      pos2.x = static_cast<float>(stoi(token));
      ss >> token;
      pos2.y = static_cast<float>(stoi(token));

      // build line
      auto line = buildLine(pos1, pos2, color);
      setLine(line);

      return true;
    }

    return false;
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
