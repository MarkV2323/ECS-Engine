#pragma once

namespace ecse {
class ScoreComp {
 public:
  int score{0};
  ScoreComp() : score(0) {}
  ScoreComp(int s) : score(s) {}
  ~ScoreComp() {}
};
}  // namespace ecse