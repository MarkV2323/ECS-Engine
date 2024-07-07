#pragma once

#include <memory>
#include <string>

#include "CollisionComp.h"
#include "InputComp.h"
#include "LifespanComp.h"
#include "ScoreComp.h"
#include "ShapeComp.h"
#include "TransformComp.h"

namespace ecse {
class Entity {
 private:
  std::string tag{"null_tag"};
  bool active{true};
  size_t id{0};

  Entity() {}

  // Player Entity Constructor
  Entity(std::string eTag) : tag(eTag) {}

 public:
  friend class EntityManager;

  std::shared_ptr<CollisionComp> cCollision;
  std::shared_ptr<InputComp> cInput;
  std::shared_ptr<LifespanComp> cLifespan;
  std::shared_ptr<ScoreComp> cScore;
  std::shared_ptr<ShapeComp> cShape;
  std::shared_ptr<TransformComp> cTransform;

  ~Entity(){};

  void destroy() { active = false; }

  bool isActive() { return active; }

  const std::string& getTag() { return tag; }

  size_t getId() { return id; }

  std::string printEntityInfo() {
    std::string r_string = "";
    r_string += "ID:     " + std::to_string(id) + "\n";
    r_string += "TAG:    " + tag + "\n";
    r_string += "ACTIVE: " + std::to_string(active) + "\n";
    r_string += (cCollision) ? "cCollision: TRUE\n" : "cCollision: FALSE\n";
    r_string += (cInput) ? "cInput:     TRUE\n" : "cInput:     FALSE\n";
    r_string += (cLifespan) ? "cLifespan:  TRUE\n" : "cLifespan:  FALSE\n";
    r_string += (cScore) ? "cScore:     TRUE\n" : "cScore:     FALSE\n";
    r_string += (cTransform) ? "cTransform: TRUE" : "cTransform: FALSE";
    return r_string;
  }
};
}