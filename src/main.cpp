#include <SFML/Graphics.hpp>

#include "entity_manager.hpp"
#include "system_cursorMovement.hpp"
#include "system_draw.hpp"
#include "system_input.hpp"
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

  Entity e1;
  e1.setName("Mark");
  e1.setRec(buildRec(Color::Green, {20.f, 20.f}, {300.f, 300.f}));
  e1.setSpeed({1.31f, 1.31f});
  e1.setPlayer();
  eman.AddEntity(e1);

  Entity e2;
  e2.setName("Alan");
  Vector2f p1{100.f, 200.f};
  Vector2f p2{600.f, 600.f};
  e2.setLine(buildLine(p1, p2, Color::Yellow));
  eman.AddEntity(e2);

  //  fmt::print(fg(INFO_COLOR), "{}", "Line Segment: ");
  //  fmt::print(fg(VAL_COLOR), "{} to {}\n", printVector(p1), printVector(p2));

  //  auto intersects = calcBoundIntersects(p1, p2);

  //  auto rec = buildRec();
  //  auto localBounds = rec.getLocalBounds();
  //  fmt::print("{},{}\n", localBounds.size.x, localBounds.size.y);

  while (window.isOpen()) {
    // process any input
    ProcessWindowEvent(window);

    if (game_paused && !increment_frame) continue;

    // process systems
    // PlayerFollowCursor(window, eman);
    ProcessEntityMovement(window, eman);

    // process drawing
    DrawEman(window, eman);

    if (game_paused && increment_frame) increment_frame = false;

  }
}
