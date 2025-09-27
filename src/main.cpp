#include <fmt/base.h>
#include <fmt/color.h>
#include <fmt/format.h>

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "utils.hpp"

using namespace std;
using namespace sf;

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
//  EntityMan eman = {};
//  printConstants();

//  Entity e;
//  e.setName("Mark");
//  e.setRec(buildRec(Color::Green, {20.f, 20.f}, {300.f, 300.f}));
//  eman.addEntity(e);

//  Entity e2;
//  e.setName("Alan");
//  Vector2f p1{100.f, 200.f};
//  Vector2f p2{600.f, 600.f};
//  e.setLine(buildLine(p1, p2, Color::Yellow));
//  eman.addEntity(e);

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
    //physics(eman);

    // process drawing
    //draw(window, eman);
  }
}
