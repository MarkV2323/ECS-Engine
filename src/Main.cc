#include <SFML/Graphics.hpp>
#include <iostream>

// All Components
#include "CollisionComp.h"
#include "InputComp.h"
#include "LifespanComp.h"
#include "ScoreComp.h"
#include "ShapeComp.h"
#include "TransformComp.h"

// For ease of use, use both std & our custom ecse namespaces
using namespace std;
using namespace ecse;

/**
 * This Main program is used simply as a quick test bench for changes
 * in the ECS-Engine library.
 */
int main(int argc, char const *argv[]) {
  cout << "Hello World!\n";
  return 0;
}