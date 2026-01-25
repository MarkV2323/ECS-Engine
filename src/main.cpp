#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "entity_manager.hpp"
#include "globals.hpp"
#include "system_animation.hpp"
#include "system_collision.hpp"
#include "system_cursorMovement.hpp"
#include "system_draw.hpp"
#include "system_input.hpp"
#include "system_marshal.hpp"
#include "system_movement.hpp"
#include "textures.hpp"
#include "utils.hpp"

using namespace std;
using namespace sf;
using namespace ecs;

inline void ProcessWindowEvent(RenderWindow& win, EntityMan& eman) {
  while (const optional event = win.pollEvent()) {
    if (event->is<Event::Closed>()) win.close();
    if (event->is<Event::KeyPressed>()) {
      ProcessInput(win, eman, event.value().getIf<Event::KeyPressed>()->code);
    }
  }
}

int main() {
  RenderWindow window(VideoMode({WIN_WIDTH, WIN_HEIGHT}), "SFML works!");
  window.setFramerateLimit(FRAME_RATE);

  // load entities from a config file
  ProcessUnmarshalEntityMan(eman);

  // print loaded textures
  tman.PrintLoadedTextures();

  while (window.isOpen()) {
    // process any input
    ProcessWindowEvent(window, eman);

    if (game_paused && !increment_frame) continue;

    // process systems
    // PlayerFollowCursor(window, eman);
    ProcessRealInput(eman);
    ProcessEntityMovement(window, eman);
    ProcessCollisions(eman);
    ProcessAnimations();

    // process drawing
    DrawEman(window, eman);

    // process log
    if (log_frame) {
      for (auto& e : eman.entities) {
        if (e.shapeRec) fmt::print("{}\n", e.Log());
        if (e.shapeSprite) fmt::print("{}\n", e.Log());
        if (e.shapeCir) fmt::print("{}\n", e.Log());
        if (e.shapeLine) fmt::print("{}\n", e.Log());
      }
    }

    if (game_paused && increment_frame) increment_frame = false;
  }
}
