#include <SFML/Graphics.hpp>
#include <iostream>

// All Components
#include "EcsHeaders/CollisionComp.h"
#include "EcsHeaders/InputComp.h"
#include "EcsHeaders/LifespanComp.h"
#include "EcsHeaders/ScoreComp.h"
#include "EcsHeaders/ShapeComp.h"
#include "EcsHeaders/TransformComp.h"

// Entity classes
#include "EcsHeaders/EntityManager.h"

// For ease of use, use both std & our custom ecse namespaces
using namespace std;
using namespace ecse;

/**
 * This Main program is used simply as a quick test bench for changes
 * in the ECS-Engine library.
 */
int main(int argc, char const *argv[]) {
  cout << "Hello World!\n";
  EntityManager eMan{};
  eMan.addEntity("player");
  return 0;
}