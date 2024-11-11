#pragma once
#include "obstacle.h"
#include "spaceship.h"
#include "aliens.h"

class Game
{
public:
  Game();
  ~Game();
  void Draw();
  void Update();
  void HandleInput();

private:
  void DeleteInactiveLasers();
  std::vector<Obstacle> createObstacles();
  std::vector<Alien> createAliens();
  Spaceship spaceship;
  std::vector<Obstacle> obstacles;
  std::vector<Alien> aliens;
  void moveAliens();
  void AliensShooter();

  int alienDirection;
  void moveAliensDown();
  std::vector<Laser> alienLasers;
  constexpr static float timeAlienShootingInterval = 0.3;
  float timeAlienShooting;
};
