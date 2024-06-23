#pragma once

namespace ecse {
class CollisionComp {
 public:
  float radius{0.0};
  CollisionComp() : radius(0.0) {}
  CollisionComp(float r) : radius(r) {}
  ~CollisionComp() {}
};
}  // namespace ecse