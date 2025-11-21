#pragma once

#include <fmt/color.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

namespace ecs {
constexpr int WIN_WIDTH = 600;
constexpr int WIN_HEIGHT = 600;
constexpr int FRAME_RATE = 60;

constexpr sf::Vector2f TOP_LEFT{0.f, 0.f};
constexpr sf::Vector2f TOP_RIGHT{WIN_WIDTH, 0.f};
constexpr sf::Vector2f BOT_LEFT{0.f, WIN_HEIGHT};
constexpr sf::Vector2f BOT_RIGHT{WIN_WIDTH, WIN_HEIGHT};

constexpr fmt::rgb INFO_COLOR = (0xFABD2F);
constexpr fmt::rgb VAL_COLOR = (0xEBDBB2);
}  // namespace ecs

inline std::string PrintVector(sf::Vector2f p) {
  return fmt::format("({:.2f},{:.2f})", p.x, p.y);
}

inline void PrintConstants() {
  using namespace ecs;

  fmt::print(fg(INFO_COLOR), "{:>11}", "WIDTH:");
  fmt::print(fg(VAL_COLOR), "{}\n", WIN_WIDTH);

  fmt::print(fg(INFO_COLOR), "{:>11}", "HEIGHT:");
  fmt::print(fg(VAL_COLOR), "{}\n", WIN_HEIGHT);

  fmt::print(fg(INFO_COLOR), "{:>11}", "TOP_LEFT:");
  fmt::print(fg(VAL_COLOR), "{}\n", PrintVector(TOP_LEFT));

  fmt::print(fg(INFO_COLOR), "{:>11}", "TOP_RIGHT:");
  fmt::print(fg(VAL_COLOR), "{}\n", PrintVector(TOP_RIGHT));

  fmt::print(fg(INFO_COLOR), "{:>11}", "BOT_LEFT:");
  fmt::print(fg(VAL_COLOR), "{}\n", PrintVector(BOT_LEFT));

  fmt::print(fg(INFO_COLOR), "{:>11}", "BOT_RIGHT:");
  fmt::print(fg(VAL_COLOR), "{}\n", PrintVector(BOT_RIGHT));
}

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
