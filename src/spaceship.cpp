#include "spaceship.h"

Spaceship::Spaceship()
{

  image = LoadTexture("Graphics/spaceship.png");
  float margin = 40.0f;
  float screenWidth = GetScreenWidth() - (2 * margin);
  float screenHeight = GetScreenHeight() - (2 * margin);

  // Initialize spaceship position at bottom center of screen
  float spaceshipX = margin + screenWidth / 2.0f - 32; // 32 is half the spaceship width
  float spaceshipY = GetScreenHeight() - margin - 60;
  timeFire = 0.0;
}

Spaceship::~Spaceship() { UnloadTexture(image); }

void Spaceship::Draw() { DrawTextureV(image, position, WHITE); }

void Spaceship::MoveLeft()
{
  position.x -= 7;
  if (position.x < 0)
  {
    position.x = 0;
  }
}
void Spaceship::MoveRight()
{
  position.x += 7;
  if (position.x > GetScreenWidth() - image.width)
  {
    position.x = GetScreenWidth() - image.width;
  }
}
void Spaceship::FireLaser()
{
  if (GetTime() - timeFire > 0.2)
  {
    lasers.push_back(Laser({position.x + image.width / 2 - 2, position.y}, -6));
    timeFire = GetTime();
  }
}

Rectangle Spaceship::GetRectangle()
{
  float paddingX = 70.0f; // Horizontal padding
  float paddingY = 50.0f; // Vertical padding
  return Rectangle{
      position.x + paddingX,        // X position with padding from left
      position.y + paddingY,        // Y position with padding from top
      image.width - (2 * paddingX), // Width reduced by padding on both sides
      image.height - (2 * paddingY) // Height reduced by padding on top and bottom
  };
}

void Spaceship::Reset()
{
  float margin = 40.0f;
  float screenWidth = GetScreenWidth() - (2 * margin);
  float screenHeight = GetScreenHeight() - (2 * margin);

  // Initialize spaceship position at bottom center of screen
  float spaceshipX = margin + screenWidth / 2.0f - 32; // 32 is half the spaceship width
  float spaceshipY = GetScreenHeight() - margin - 60;
  lasers.clear();
}
