#include "game.h"
#include <raylib-cpp.hpp>
typedef enum GameScreen
{
  LOGO = 0,
  TITLE,
  GAMEPLAY,

} gameScreens;
int main()
{

  Color grey = {29, 29, 27, 255};
  // Initialization
  int screenWidth = 1280;
  int screenHeight = 960;

  InitWindow(screenWidth, screenHeight, "game test");
  GameScreen currentScreen = LOGO;
  SetTargetFPS(60);
  int framesCounter = 0;
  Game game;
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    // Update
    switch (currentScreen)
    {
    case LOGO:
    {
      framesCounter++;
      if (framesCounter > 240)
      {
        currentScreen = TITLE;
      }
    }
    break;
    case TITLE:
    {
      if (IsKeyPressed(KEY_ENTER))
      {
        currentScreen = GAMEPLAY;
      }
    }
    break;
    case GAMEPLAY:
    {
      game.HandleInput();
      game.Update();
    }
    break;
    default:
      break;
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);

    switch (currentScreen)
    {
    case LOGO:
    {
      // TODO: Draw LOGO screen here!
      DrawText("OOP PROJECT : SPACE INVADER", 20, 20, 40, LIGHTGRAY);
      DrawText("WAIT for 4 SECONDS...", 290, 220, 20, GRAY);
    }
    break;
    case TITLE:
    {
      // TODO: Draw TITLE screen here!
      DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
      DrawText("MENU", 20, 20, 40, DARKGREEN);
      DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);
    }
    break;
    case GAMEPLAY:
    {
      ClearBackground(grey);
      game.Draw();
    }
    break;
    default:
      break;
    }
    EndDrawing();
  }
  return 0;
}
