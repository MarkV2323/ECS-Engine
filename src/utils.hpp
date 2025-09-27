#pragma once

#include <fmt/color.h>

#include <SFML/System/Vector2.hpp>
#include <string>

namespace ecs {
  constexpr int WIN_WIDTH = 600;
  constexpr int WIN_HEIGHT = 600;

  constexpr sf::Vector2f TOP_LEFT{0.f, 0.f};
  constexpr sf::Vector2f TOP_RIGHT{WIN_WIDTH, 0.f};
  constexpr sf::Vector2f BOT_LEFT{0.f, WIN_HEIGHT};
  constexpr sf::Vector2f BOT_RIGHT{WIN_WIDTH, WIN_HEIGHT};

  constexpr fmt::rgb INFO_COLOR = (0xFABD2F);
  constexpr fmt::rgb VAL_COLOR = (0xEBDBB2);
}

std::string printVector(sf::Vector2f p) {
  return fmt::format("({:.2f},{:.2f})", p.x, p.y);
}

void printConstants() {
  using namespace ecs;

  fmt::print(fg(INFO_COLOR), "{:>11}", "WIDTH:");
  fmt::print(fg(VAL_COLOR), "{}\n", WIN_WIDTH);

  fmt::print(fg(INFO_COLOR), "{:>11}", "HEIGHT:");
  fmt::print(fg(VAL_COLOR), "{}\n", WIN_HEIGHT);

  fmt::print(fg(INFO_COLOR), "{:>11}", "TOP_LEFT:");
  fmt::print(fg(VAL_COLOR), "{}\n", printVector(TOP_LEFT));

  fmt::print(fg(INFO_COLOR), "{:>11}", "TOP_RIGHT:");
  fmt::print(fg(VAL_COLOR), "{}\n", printVector(TOP_RIGHT));

  fmt::print(fg(INFO_COLOR), "{:>11}", "BOT_LEFT:");
  fmt::print(fg(VAL_COLOR), "{}\n", printVector(BOT_LEFT));

  fmt::print(fg(INFO_COLOR), "{:>11}", "BOT_RIGHT:");
  fmt::print(fg(VAL_COLOR), "{}\n", printVector(BOT_RIGHT));
}
