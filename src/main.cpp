#include <SFML/Graphics.hpp>

#include "entity_manager.hpp"
#include "system_collision.hpp"
#include "system_cursorMovement.hpp"
#include "system_draw.hpp"
#include "system_input.hpp"
#include "system_marshal.hpp"
#include "system_movement.hpp"
#include "utils.hpp"

using namespace std;
using namespace sf;
using namespace ecs;

void ProcessWindowEvent(RenderWindow& win) {
  while (const optional event = win.pollEvent()) {
    if (event->is<Event::Closed>()) win.close();
    if (event->is<Event::KeyPressed>()) {
      ProcessInput(win, event.value().getIf<Event::KeyPressed>()->code);
    }
  }
}

int main() {
  RenderWindow window(VideoMode({WIN_WIDTH, WIN_HEIGHT}), "SFML works!");
  window.setFramerateLimit(FRAME_RATE);
  EntityMan eman = {};

  // Load entities from a config file
  processUnmarshalEntityMan(eman);

  // Call the Marshal System to save the entities
  // ProcessMarshalEntityMan(eman);

  while (window.isOpen()) {
    // process any input
    ProcessWindowEvent(window);

    if (game_paused && !increment_frame) continue;

    // process systems
    // PlayerFollowCursor(window, eman);
    ProcessEntityMovement(window, eman);
    ProcessCollisions(eman);

    // process drawing
    DrawEman(window, eman);

    // process log
    if (log_frame) {
      for (auto& e : eman.entities) {
        if (e.shapeRec) fmt::print("{}\n", e.log());
        if (e.shapeLine) fmt::print("{}\n", e.log());
      }
    }

    if (game_paused && increment_frame) increment_frame = false;
  }
}
