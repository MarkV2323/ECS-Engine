#pragma once

#include <math.h>

#include <SFML/System/Vector2.hpp>
#include <string>

namespace ecse {
class GameVector {
 private:
  void calculateMag() {
    // ||v|| = sqrt ( (q1 - p1)^2 + (q2 - p2)^2 )
    // ||v|| = sqrt ( (v1)^2 + (v2)^2 )
    _mag = sqrt((_comp.x * _comp.x) + (_comp.y * _comp.y));
  }

  void calculateAngle() {
    // 0 = arctan(v2 / v1)
    _angle = atan(_comp.y / _comp.x) * 180 / 3.14159265;
  }

  GameVector(){};

 public:
  sf::Vector2f _comp{0.0f, 0.0f};
  float _mag{0.0f};
  float _angle{0.0f};

  // Three ways to create a vector object:
  // 1: From two points, you can calculate the component form, then calculate
  //    the angle & magnitude.
  // 2: From component form, then calculate the angle & magnitude.
  // 3: From angle & magnitude then calculate the component form.
  GameVector(sf::Vector2f& p, sf::Vector2f& q) {
    // <v1,v2> = <q1 - p1, q2 - p2>
    _comp.x = q.x - p.x;
    _comp.y = q.y - p.y;
    calculateMag();
    calculateAngle();
  }

  GameVector(sf::Vector2f& c) {
    calculateMag();
    calculateAngle();
  }

  GameVector(float a, float m) : _angle{a}, _mag{m} {}

  // Return resulant vector sum.
  GameVector add(GameVector& v) {
    // u + v = <u1 + v1, u2 + v2>
    return GameVector(
        sf::Vector2f((_comp.x + v._comp.x), (_comp.y + v._comp.y)));
  }

  // Return difference vector.
  GameVector diff(GameVector& v) {
    // u + (-v) = <u1 - v1, u2 - v2>
    return add(v.neg());
  }

  // Return scalar multiple vector.
  GameVector scale(float c) {
    // cu = <c * u1, c * u2>
    return GameVector(sf::Vector2f((c * _comp.x), (c * _comp.y)));
  }

  // Return negative vector.
  GameVector neg() {
    // -1u = <-1 * u1, -1 * u2>
    return scale(-1);
  }

  // Return a unit vector.
  GameVector unit() {
    // u = (1 / ||v||) * v
    return scale((1 / _mag));
  }

  // Return human readble string of all private member data.
  std::string toString() {
    return "<" + std::to_string(_comp.x) + "," + std::to_string(_comp.y) +
           "> " + std::to_string(_angle) + "o |" + std::to_string(_mag) + "|";
  }

  ~GameVector(){};
};
}