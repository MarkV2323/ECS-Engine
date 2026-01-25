#pragma once

#include <fmt/color.h>

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <filesystem>
#include <string>

namespace ecs {

// contains working directory of binary
const std::filesystem::path CWD = std::filesystem::current_path();
constexpr static std::string TEXTURE_PATH = "assests";
const std::filesystem::path textPath = CWD / TEXTURE_PATH;

// window related vars
constexpr int WIN_WIDTH = 600;
constexpr int WIN_HEIGHT = 600;
constexpr int FRAME_RATE = 60;
constexpr sf::Vector2f TOP_LEFT{0.f, 0.f};
constexpr sf::Vector2f TOP_RIGHT{WIN_WIDTH, 0.f};
constexpr sf::Vector2f BOT_LEFT{0.f, WIN_HEIGHT};
constexpr sf::Vector2f BOT_RIGHT{WIN_WIDTH, WIN_HEIGHT};

// log colors
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
