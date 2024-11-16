#pragma once
#include "lasers.h"
class Spaceship
{
public:
  Spaceship();
  ~Spaceship();
  void Draw();
  void MoveLeft();
  void MoveRight();
  void FireLaser();
  Rectangle GetRectangle();
  void Reset();
  std::vector<Laser> lasers;
  Vector2 position;

private:
  Texture2D image;

  double timeFire;
};
