#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>

#include "entity_manager.hpp"
#include "system_marshal.hpp"
#include "utils.hpp"

namespace ecs {

constexpr sf::Keyboard::Key CLOSE_KEY = sf::Keyboard::Key::Escape;
constexpr sf::Keyboard::Key PAUSE_KEY = sf::Keyboard::Key::P;
constexpr sf::Keyboard::Key INC_KEY = sf::Keyboard::Key::I;
constexpr sf::Keyboard::Key SAVE_KEY = sf::Keyboard::Key::S;
constexpr sf::Keyboard::Key LOG_KEY = sf::Keyboard::Key::L;
constexpr sf::Keyboard::Key UP_KEY = sf::Keyboard::Key::Up;
constexpr sf::Keyboard::Key DOWN_KEY = sf::Keyboard::Key::Down;
constexpr sf::Keyboard::Key LEFT_KEY = sf::Keyboard::Key::Left;
constexpr sf::Keyboard::Key RIGHT_KEY = sf::Keyboard::Key::Right;

bool game_paused = false;
bool increment_frame = false;
bool log_frame = false;

inline void ProcessRealInput(EntityMan& eman) {
  if (sf::Keyboard::isKeyPressed(UP_KEY)) {
    fmt::print(fg(INFO_COLOR), "{}\n", "UP pressed!");
    for (auto& e : eman.entities) {
      if (!e.player || !e.shapeSprite || !e.speed) continue;
      e.MovePos({0.f, e.speed->y * -1});
    }
  } else if (sf::Keyboard::isKeyPressed(DOWN_KEY)) {
    fmt::print(fg(INFO_COLOR), "{}\n", "DOWN pressed!");
    for (auto& e : eman.entities) {
      if (!e.player || !e.shapeSprite || !e.speed) continue;
      e.MovePos({0.f, e.speed->y});
    }
  } else if (sf::Keyboard::isKeyPressed(LEFT_KEY)) {
    fmt::print(fg(INFO_COLOR), "{}\n", "LEFT pressed!");
    for (auto& e : eman.entities) {
      if (!e.player || !e.shapeSprite || !e.speed) continue;
      e.MovePos({e.speed->x * -1, 0.f});
    }
  } else if (sf::Keyboard::isKeyPressed(RIGHT_KEY)) {
    fmt::print(fg(INFO_COLOR), "{}\n", "RIGHT pressed!");
    for (auto& e : eman.entities) {
      if (!e.player || !e.shapeSprite || !e.speed) continue;
      e.MovePos({e.speed->x, 0.f});
    }
  }
}

inline void ProcessInput(sf::RenderWindow& win, EntityMan& eman,
                         sf::Keyboard::Key key) {
  switch (key) {
    case (CLOSE_KEY):
      win.close();
      break;
    case (PAUSE_KEY):
      game_paused = !game_paused;
      fmt::print(fg(INFO_COLOR), "{} : {}\n", "Game pause", game_paused);
      break;
    case (INC_KEY):
      fmt::print(fg(INFO_COLOR), "{}\n", "Game incremented!");
      game_paused = true;
      increment_frame = true;
      break;
    case (SAVE_KEY):
      fmt::print(fg(INFO_COLOR), "{}\n", "Entities saved!");
      ProcessMarshalEntityMan(eman);
      break;
    case (LOG_KEY):
      fmt::print(fg(INFO_COLOR), "{}\n", "Logging toggled!");
      log_frame = !log_frame;
      break;
    default:
      break;
  }
}

}  // namespace ecs
