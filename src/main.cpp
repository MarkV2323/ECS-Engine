#include <SFML/Graphics.hpp>

#include "entity_manager.hpp"
#include "system_draw.hpp"
#include "utils.hpp"

using namespace std;
using namespace sf;
using namespace ecs;

void processWindowEvent(RenderWindow& win) {
  while (const optional event = win.pollEvent()) {
    if (event->is<Event::Closed>()) win.close();
    if (event->is<Event::KeyPressed>()) {
      if (event.value().getIf<Event::KeyPressed>()->code ==
          Keyboard::Key::Escape)
        win.close();
    }
  }
}

int main() {
  RenderWindow window(VideoMode({WIN_WIDTH, WIN_HEIGHT}), "SFML works!");
  EntityMan eman = {};

  Entity e1;
  e1.setName("Mark");
  e1.setRec(buildRec(Color::Green, {20.f, 20.f}, {300.f, 300.f}));
  eman.addEntity(e1);

  Entity e2;
  e2.setName("Alan");
  Vector2f p1{100.f, 200.f};
  Vector2f p2{600.f, 600.f};
  e2.setLine(buildLine(p1, p2, Color::Yellow));
  eman.addEntity(e2);

  //  fmt::print(fg(INFO_COLOR), "{}", "Line Segment: ");
  //  fmt::print(fg(VAL_COLOR), "{} to {}\n", printVector(p1), printVector(p2));

  //  auto intersects = calcBoundIntersects(p1, p2);

  //  auto rec = buildRec();
  //  auto localBounds = rec.getLocalBounds();
  //  fmt::print("{},{}\n", localBounds.size.x, localBounds.size.y);

  while (window.isOpen()) {
    // process any input
    processWindowEvent(window);

    // process physics
    // physics(eman);

    // process drawing
    draw(window, eman);
  }
}
