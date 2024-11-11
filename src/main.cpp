#include "game.h"
#include <raylib-cpp.hpp>
int main() {
  Color grey = {29, 29, 27, 255};
  // Initialization
  int screenWidth = 1280;
  int screenHeight = 960;

  InitWindow(screenWidth, screenHeight, "game test");

  SetTargetFPS(60);
  Game game;
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update

    // Draw
    
    game.HandleInput();
    game.Update();
    BeginDrawing();

    ClearBackground(grey);
    game.Draw();
    EndDrawing();
  }

  return 0;
}
