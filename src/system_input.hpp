#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
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

bool game_paused = false;
bool increment_frame = false;
bool log_frame = false;

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
