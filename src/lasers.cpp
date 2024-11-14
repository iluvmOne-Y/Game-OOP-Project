#include "lasers.h"

Laser::Laser(Vector2 position, int speed)
{
  this->position = position;
  this->speed = speed;
  active = true;
}

void Laser::Draw()
{
  if (active)
  {
    DrawRectangle(position.x, position.y, 4, 15, {253, 249, 0, 255});
  }
}
void Laser::Update()
{
  position.y += speed;
  if (position.y > GetScreenHeight() || position.y < 0)
  {
    active = false;
  }
}

Rectangle Laser::GetRectangle()
{
  Rectangle rect;
  rect.x = position.x;
  rect.y = position.y;
  rect.width = 4;
  rect.height = 15;
  return rect;
}
