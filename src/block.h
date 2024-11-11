#pragma once

#include <raylib-cpp.hpp>

class Block
{
public:
  Block(Vector2 position);
  void Draw();

private:
  Vector2 position;
};
