#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdint>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

#include "textures.hpp"
#include "utils.hpp"

inline sf::CircleShape BuildCir(sf::Color c = sf::Color::Red, float r = 4.f,
                                sf::Vector2f pos = {20.f, 20.f}) {
  sf::CircleShape circle;
  circle.setFillColor(c);
  circle.setRadius(r);
  circle.setOrigin({r, r});
  circle.setPosition(pos);
  return circle;
}

inline sf::RectangleShape BuildRec(sf::Color c = sf::Color::Blue,
                                   sf::Vector2f size = {8.f, 8.f},
                                   sf::Vector2f pos = {20.f, 20.f}) {
  sf::RectangleShape rectangle;
  rectangle.setFillColor(c);
  rectangle.setSize(size);
  rectangle.setPosition(pos);
  return rectangle;
}

inline sf::VertexArray BuildLine(sf::Vector2f p1 = {0.f, 0.f},
                                 sf::Vector2f p2 = {1.f, 1.f},
                                 sf::Color c = sf::Color::Red) {
  sf::VertexArray line(sf::PrimitiveType::Lines, 2);
  line[0].position = p1;
  line[1].position = p2;
  line[0].color = c;
  line[1].color = c;
  return line;
}

inline sf::Sprite BuildSprite(sf::IntRect ir = {{0, 0}, {64, 64}},
                              sf::Vector2f pos = {20.f, 20.f},
                              std::string textureName = {}) {
  sf::Sprite s(ecs::tman.GetTexture(textureName));
  s.setTextureRect(ir);
  s.setPosition(pos);
  return s;
}

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

  // components for an entity
  std::optional<sf::RectangleShape> shapeRec = std::nullopt;
  std::optional<sf::CircleShape> shapeCir = std::nullopt;
  std::optional<sf::VertexArray> shapeLine = std::nullopt;
  std::optional<sf::Sprite> shapeSprite = std::nullopt;
  std::optional<sf::Vector2f> speed = std::nullopt;
  std::optional<bool> player = std::nullopt;

  // Animation related vars
  bool animations {false};
  
  // These are stored window "global" positions for the rectangle.
  sf::Vector2f recCenter{0, 0};
  sf::Vector2f recSize{0, 0};
  sf::Vector2f recBounds[4];

  // "Move" a position for a shape
  void MovePos(sf::Vector2f m) {
    if (shapeRec) {
      shapeRec->move(m);
      UpdateRecData();
    }
    if (shapeCir) {
      shapeCir->move(m);
    }
    if (shapeSprite) {
      shapeSprite->move(m);
    }
  }

  // "Set" a position for a shape
  void SetPos(sf::Vector2f p) {
    if (shapeRec) {
      shapeRec->setPosition(p);
      UpdateRecData();
    }
    if (shapeCir) {
      shapeCir->setPosition(p);
    }
    if (shapeSprite) {
      shapeSprite->setPosition(p);
    }
  }

  void SetName(std::string s) { name = s; }
  void SetSpeed(sf::Vector2f v) { speed = v; }
  void SetPlayer() { player = true; }

  // Set a rectangles components
  void SetRec(sf::RectangleShape s) {
    shapeRec = s;
    shapeCir = std::nullopt;
    shapeLine = std::nullopt;
    speed = {0.05f, 0.05f};
    UpdateRecData();
  }

  // Set a circles components
  void SetCir(sf::CircleShape s) {
    shapeRec = std::nullopt;
    shapeCir = s;
    shapeLine = std::nullopt;
    speed = {0.005f, 0.005f};
  }

  // Set a lines components
  void SetLine(sf::VertexArray l) {
    shapeRec = std::nullopt;
    shapeCir = std::nullopt;
    shapeLine = l;
    speed = std::nullopt;
  }

  // Set a sprites components
  void SetSprite(sf::Sprite s) {
    shapeRec = std::nullopt;
    shapeCir = std::nullopt;
    shapeLine = std::nullopt;
    shapeSprite = s;
    animations = true;
    speed = {0.05f, 0.05f};
  }

  // Marshal an Entity to a string
  std::string Marshal() {
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

    // Name Circle R G B POS_X POS_Y R player
    if (shapeCir && speed) {
      mStr += fmt::format("{} ", name);
      mStr += fmt::format("{} ", "Circle");
      mStr += fmt::format("{} ", shapeCir->getFillColor().r);
      mStr += fmt::format("{} ", shapeCir->getFillColor().g);
      mStr += fmt::format("{} ", shapeCir->getFillColor().b);
      mStr += fmt::format("{} ", shapeCir->getPosition().x);
      mStr += fmt::format("{} ", shapeCir->getPosition().y);
      mStr += fmt::format("{} ", shapeCir->getRadius());
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

  // Retreive an entities information from a string.
  bool Unmarshal(std::string s) {
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
      auto recShape = BuildRec(color, size, pos);

      // set rectangleShape
      SetRec(recShape);

      // set speed
      speed = spd;

      return true;
    }

    if (token == "Circle") {
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
      float radius = 0.f;
      ss >> token;
      radius = static_cast<float>(stoi(token));

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
      auto cirShape = BuildCir(color, radius, pos);

      // set rectangleShape
      SetCir(cirShape);

      // set speed
      speed = spd;

      return true;
    }

    if (token == "Line") {
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
      auto line = BuildLine(pos1, pos2, color);
      SetLine(line);

      return true;
    }

    if (token == "Sprite") {
      // build sprite pos_rect
      sf::Vector2i topLeftPos{};
      ss >> token;
      topLeftPos.x = stoi(token);
      ss >> token;
      topLeftPos.y = stoi(token);

      sf::Vector2i widthHeight{};
      ss >> token;
      widthHeight.x = stoi(token);
      ss >> token;
      widthHeight.y = stoi(token);

      sf::IntRect spriteBounds{topLeftPos, widthHeight};

      // build pos
      sf::Vector2f pos;
      ss >> token;
      pos.x = static_cast<float>(stoi(token));
      ss >> token;
      pos.y = static_cast<float>(stoi(token));

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
      
      // build textureName
      std::string textureName {};
      ss >> token;
      textureName = token;

      // setup entity components
      auto spriteShape = BuildSprite(spriteBounds, pos, textureName);
      SetSprite(spriteShape);
      speed = spd;
      
      return true;
    }

    return false;
  }

  // Log an entities information to the console
  std::string Log() {
    std::string logString = "";
    if (shapeSprite) {
      // Type : Val - Name : Val - centerPos : Val - Spd : Val - Player : Val
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Type");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", "Sprite");
      logString += " - ";
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Name");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", name);
      logString += " - ";
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "topLeftPos");
      auto pPos = shapeSprite->getPosition();
      logString +=
          fmt::format(fg(VAL_COLOR), "{:<10}", PrintVector(pPos));
      logString += " - ";
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Spd");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", PrintVector(*speed));
      logString += " - ";
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Player");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", *player);
      return logString;
    }

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
          fmt::format(fg(VAL_COLOR), "{:<10}", PrintVector(recBounds[0]));
      logString += " - ";
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Spd");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", PrintVector(*speed));
      logString += " - ";
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Player");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", *player);
      return logString;
    }
    if (shapeCir) {
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Type");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", "Circle");
      logString += " - ";
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Name");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", name);
      logString += " - ";
      logString += fmt::format(fg(INFO_COLOR), "{} : ", "Spd");
      logString += fmt::format(fg(VAL_COLOR), "{:<10}", PrintVector(*speed));
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

