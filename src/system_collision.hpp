#pragma once

#include "entity_manager.hpp"
#include "system_input.hpp"

namespace ecs {

enum class Intersections {
  None = 0,
  Top = 1 << 0,
  Bot = 1 << 1,
  Right = 1 << 2,
  Left = 1 << 3,
  Top_Right = 5,
  Top_Left = 9,
  Bot_Right = 6,
  Bot_Left = 10
};

std::string ToString(Intersections i) {
  switch (i) {
    case Intersections::None:
      return "None";
    case Intersections::Top:
      return "Top";
    case Intersections::Bot:
      return "Bot";
    case Intersections::Right:
      return "Right";
    case Intersections::Left:
      return "Left";
    case Intersections::Top_Right:
      return "Top_Right";
    case Intersections::Top_Left:
      return "Top_Left";
    case Intersections::Bot_Right:
      return "Bot_Right";
    case Intersections::Bot_Left:
      return "Bot_Left";
    default:
      return "Unknown";
  }
}

inline Intersections operator|(Intersections a, Intersections b) {
  return static_cast<Intersections>(static_cast<int>(a) | static_cast<int>(b));
}

bool LineLineCol(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3,
                 sf::Vector2f p4) {
  float denom = ((p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y));

  float uA =
      ((p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x)) / denom;
  float uB =
      ((p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x)) / denom;

  if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
    return true;
  }
  return false;
}

bool TopLineIntersect(sf::Vector2f p1, sf::Vector2f p2) {
  return LineLineCol(p1, p2, TOP_LEFT, TOP_RIGHT);
}

bool BotLineIntersect(sf::Vector2f p1, sf::Vector2f p2) {
  return LineLineCol(p1, p2, BOT_LEFT, BOT_RIGHT);
}

bool RightLineIntersect(sf::Vector2f p1, sf::Vector2f p2) {
  return LineLineCol(p1, p2, TOP_RIGHT, BOT_RIGHT);
}

bool LeftLineIntersect(sf::Vector2f p1, sf::Vector2f p2) {
  return LineLineCol(p1, p2, TOP_LEFT, BOT_LEFT);
}

Intersections CalcBoundIntersects(sf::Vector2f p1, sf::Vector2f p2) {
  Intersections intersecs{Intersections::None};

  if (TopLineIntersect(p1, p2)) intersecs = intersecs | Intersections::Top;
  if (BotLineIntersect(p1, p2)) intersecs = intersecs | Intersections::Bot;
  if (RightLineIntersect(p1, p2)) intersecs = intersecs | Intersections::Right;
  if (LeftLineIntersect(p1, p2)) intersecs = intersecs | Intersections::Left;

  return intersecs;
}

void RectangleBounds(Entity& e) {
  auto collision = Intersections{0};
  auto p = e.shapeRec->getPosition();
  auto s = *e.speed;

  // top, bot, left, right
  collision = collision | CalcBoundIntersects(e.recBounds[0], e.recBounds[1]);
  collision = collision | CalcBoundIntersects(e.recBounds[2], e.recBounds[3]);
  collision = collision | CalcBoundIntersects(e.recBounds[0], e.recBounds[2]);
  collision = collision | CalcBoundIntersects(e.recBounds[1], e.recBounds[3]);

  switch (collision) {
    case Intersections::None:
      break;
    case Intersections::Top:
      e.movePos({0, 1});
      e.setSpeed({s.x, s.y * -1});
      break;
    case Intersections::Bot:
      e.movePos({0, -1});
      e.setSpeed({s.x, s.y * -1});
      break;
    case Intersections::Right:
      e.movePos({-1, 0});
      e.setSpeed({s.x * -1, s.y});
      break;
    case Intersections::Left:
      e.movePos({1, 0});
      e.setSpeed({s.x * -1, s.y});
      break;
    case Intersections::Top_Right:
      e.movePos({1, 1});
      e.setSpeed({s.x * -1, s.y * -1});
      break;
    case Intersections::Top_Left:
      e.movePos({-1, 1});
      e.setSpeed({s.x * -1, s.y * -1});
      break;
    case Intersections::Bot_Right:
      e.movePos({-1, -1});
      e.setSpeed({s.x * -1, s.y * -1});
      break;
    case Intersections::Bot_Left:
      e.movePos({1, -1});
      e.setSpeed({s.x * -1, s.y * -1});
      break;
    default:
      break;
  }

  if (collision != Intersections::None && log_frame) {
    fmt::print(fg(INFO_COLOR), "{}", "Found Intersection: ");
    fmt::print(fg(VAL_COLOR), "{}\n", ToString(collision));
  }
}

void RectangleCollisions(Entity& e) { RectangleBounds(e); }

void ProcessCollisions(EntityMan& eman) {
  for (auto& e : eman.entities) {
    if (e.shapeRec && e.speed) RectangleCollisions(e);
    if (e.shapeCir && e.speed) continue;
  }
}

}  // namespace ecs
