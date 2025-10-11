#pragma once

#include <SFML/Window.hpp>

#include "utils.hpp"

namespace ecs {

constexpr sf::Keyboard::Key CLOSE_KEY = sf::Keyboard::Key::Escape;
constexpr sf::Keyboard::Key PAUSE_KEY = sf::Keyboard::Key::P;
constexpr sf::Keyboard::Key INC_KEY = sf::Keyboard::Key::I;

bool game_paused = false;
bool increment_frame = false;

void ProcessInput(sf::RenderWindow& win, sf::Keyboard::Key key) {
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
    default:
      break;
  }
}

}  // namespace ecs
