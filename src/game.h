#pragma once
#include "obstacle.h"
#include "spaceship.h"
#include "aliens.h"
#include <iostream>

class Game
{
public:
  Game();
  ~Game();
  void Draw();
  void Update();
  void HandleInput();
  bool run;

private:
  void DeleteInactiveLasers();
  std::vector<Obstacle> createObstacles();
  std::vector<Alien> createAliens();
  void CheckForCollisions();
  Spaceship spaceship;
  std::vector<Obstacle> obstacles;
  std::vector<Alien> aliens;
  void MoveAliens();
  void AliensShooter();

  int aliensDirection;
  void MoveAliensDown();
  std::vector<Laser> alienLasers;
  constexpr static float timeAlienShootingInterval = 0.3;
  float timeAlienShooting;
  int lives;
  void GameOver();
  void InitGame();
  void ResetGame();
};
