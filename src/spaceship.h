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

private:
  Texture2D image;
  Vector2 position;
  double timeFire;
};
