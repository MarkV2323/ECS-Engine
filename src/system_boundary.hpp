#pragma once

#include "entity_manager.hpp"
#include "utils.hpp"

namespace ecs {

float DistPoints(sf::Vector2f p1, sf::Vector2f p2) {
  return sqrt(pow((p2.x - p1.x), 2) + pow((p2.y - p1.y), 2));
}

bool IntersectLines(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3,
                    sf::Vector2f p4) {
  // Define intersection via matrix determinants
  double denom = (p4.y - p3.y) * (p2.x - p1.x) - (p4.x - p3.x) * (p2.y - p1.y);

  // denom = 0 when line segment are parallel or coincident
  if (denom == 0) {
    float m1 = (p2.y - p1.y) / (p2.x - p1.x);
    float b1 = (p2.y - (m1 * p2.x));
    float m2 = (p4.y - p3.y) / (p4.x - p3.x);
    float b2 = (p4.y - (m1 * p4.x));

    // coincident lines have equal slopes & y intercepts
    if (m1 == m2 && b1 == b2) return true;
    return false;
  }

  double numeA = (p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x);
  double numeB = (p2.x - p1.x) * (p1.y - p3.y) - (p2.y - p1.y) * (p1.x - p3.x);

  double uA = numeA / denom;
  double uB = numeB / denom;

  if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) return true;

  return false;
}

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

// Take line segement input and determine if intersection occurs
bool TopLineIntersect(sf::Vector2f p1, sf::Vector2f p2) {
  return IntersectLines(p1, p2, TOP_LEFT, TOP_RIGHT);
}

bool BotLineIntersect(sf::Vector2f p1, sf::Vector2f p2) {
  return IntersectLines(p1, p2, BOT_LEFT, BOT_RIGHT);
}

bool RightLineIntersect(sf::Vector2f p1, sf::Vector2f p2) {
  return IntersectLines(p1, p2, TOP_RIGHT, BOT_RIGHT);
}

bool LeftLineIntersect(sf::Vector2f p1, sf::Vector2f p2) {
  return IntersectLines(p1, p2, TOP_LEFT, BOT_LEFT);
}

// Calculate if a line segment (p1, p2) touchs a bound
Intersections CalcBoundIntersects(sf::Vector2f p1, sf::Vector2f p2) {
  Intersections intersecs{Intersections::None};

  if (TopLineIntersect(p1, p2)) intersecs = intersecs | Intersections::Top;
  if (BotLineIntersect(p1, p2)) intersecs = intersecs | Intersections::Bot;
  if (RightLineIntersect(p1, p2)) intersecs = intersecs | Intersections::Right;
  if (LeftLineIntersect(p1, p2)) intersecs = intersecs | Intersections::Left;

  //fmt::print(fg(INFO_COLOR), "{}", "Found Intersection: ");
  //fmt::print(fg(VAL_COLOR), "{}\n", ToString(intersecs));

  return intersecs;
}

void RectangleBoundsColl(Entity& e) {
  auto topInter = Intersections{0};
  auto botInter = Intersections{0};
  auto combinedInter = Intersections{0};
  auto p = e.shapeRec->getPosition();

  // Only calculate top and right intersections
  topInter = CalcBoundIntersects(e.recBounds[0], e.recBounds[1]);
  botInter = CalcBoundIntersects(e.recBounds[2], e.recBounds[3]);

  // Join the intersections together
  combinedInter = topInter | botInter;
  fmt::print(fg(INFO_COLOR), "{}", "Found Intersection: ");
  fmt::print(fg(VAL_COLOR), "{}\n", ToString(combinedInter));

  switch (combinedInter) {
    case Intersections::None:
      break;
    case Intersections::Top:
      break;
    case Intersections::Bot:
      break;
    case Intersections::Right:
      break;
    case Intersections::Left:
      break;
    case Intersections::Top_Right:
      break;
    case Intersections::Top_Left:
      break;
    case Intersections::Bot_Right:
      break;
    case Intersections::Bot_Left:
      break;
    default:
      break;
  }
}

// Calculate if a collision has occured between an entity
// with a shape against the maps bounds.
void MapBoundsColl(EntityMan& eman) {
  for (auto& e : eman.entities) {
    if (e.shapeRec) {
      RectangleBoundsColl(e);
    }
  }
}

}  // namespace ecs
