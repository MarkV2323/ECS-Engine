#include <SFML/Graphics.hpp>
#include <iostream>

// All Components
#include "Component/circle_shape.h"
#include "Component/collision.h"
#include "Component/input.h"
#include "Component/lifespan.h"
#include "Component/rectangle_shape.h"
#include "Component/score.h"
#include "Component/transform.h"

// Entity classes
#include "Core/entity_manager.h"

// For ease of use, use both std & our custom ecse namespaces
using namespace std;
using namespace ecse;

// Basic "game" class
class Game {
 private:
  sf::RenderWindow window;
  EntityManager eMan;
  bool isGame = false;
  std::shared_ptr<Entity> player = nullptr;

 public:
  // Game releated constants

  const int GAME_WIDTH = 600;
  const int GAME_HEIGHT = 800;

  // Player related constants

  const float PLAYER_START_X = GAME_WIDTH / 2.0f;
  const float PLAYER_START_Y = GAME_HEIGHT - 50.0f;
  const float PLAYER_SIZE_X = 50.0f;
  const float PLAYER_SIZE_Y = 10.0f;
  const float PLAYER_SPEED = 5.0f;

  Game() {};
  ~Game() {};

  // init game
  void initGame() {
    // Init game window
    window.create(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "ECS Test Bench");
    window.setFramerateLimit(60);

    // Init entityManager
    eMan = EntityManager();

    // Setup player
    player = eMan.addEntity("player");
    initPlayer();

    eMan.update();
    std::cout << eMan.getEntitiesStats() << std::endl;

    isGame = true;
  };

  void initPlayer() {
    // Setup player with a circle shape
    // player->cShape = std::make_shared<ShapeComp>(
    //     PLAYER_SIZE_X, 4, sf::Color::White, sf::Color::Green, 2);
    // player->cShape->shape.setPosition(
    //     sf::Vector2f(PLAYER_START_X, PLAYER_START_Y));
    // player->cShape->shape.setRotation(45);

    // Setup player with a rectangle shape
    player->cRectShape = std::make_shared<RectShapeComp>(
        PLAYER_SIZE_X, PLAYER_SIZE_Y, 4, sf::Color::White, sf::Color::Green, 2);
    player->cRectShape->shape.setPosition(
        sf::Vector2f(PLAYER_START_X, PLAYER_START_Y));
    player->cRectShape->shape.setRotation(0);

    // Setup player with a controller
    player->cInput = std::make_shared<InputComp>();

    // Setup player with a transform
    player->cTransform = std::make_shared<TransformComp>(
        sf::Vector2f(PLAYER_START_X, PLAYER_START_Y),
        sf::Vector2f(PLAYER_SPEED, PLAYER_SPEED), sf::Vector2f(0.0f, 0.0f),
        0.0f);
  }

  sf::RenderWindow& getWindow() { return window; }

  const bool& getIsGame() { return isGame; }

  // systems
  void drawFrameSystem() {
    window.clear(sf::Color::Black);
    // Display all entitie that have a shape comp
    for (auto& e : eMan.getEntities()) {
      if (e->cShape != nullptr) {
        window.draw(e->cShape->shape);
      } else if (e->cRectShape != nullptr) {
        window.draw(e->cRectShape->shape);
      }
    }
    window.display();
  };
};

/**
 * This Main program is used simply as a quick test bench for changes
 * in the ECS-Engine library.
 */
int main(int argc, char const* argv[]) {
  // Create and init our game object.
  cout << "Initlizating TestBench..." << endl;
  Game game{};
  game.initGame();

  // Enter main game loop
  while (game.getWindow().isOpen()) {
    // Handle Window events
    sf::Event event;
    while (game.getWindow().pollEvent(event)) {
      // close event
      if (event.type == sf::Event::Closed) {
        game.getWindow().close();
      }
    }

    // Our "frame" will be calculated here.
    // Some "Systems" in our frame we may want
    // 1) Render system
    game.drawFrameSystem();
  }
  return 0;
}