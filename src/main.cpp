#include "game.h"
#include <raylib-cpp.hpp>

typedef enum GameScreen
{
  LOGO = 0,
  TITLE,
  GAMEPLAY,
} GameScreen;
/*void toogleFullscreen()
{
  if (!IsWindowFullscreen())
  {
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    ToggleFullscreen();
  }
  else
  {
    ToggleFullscreen();
  }
}*/
int main()
{
  ;
  Color grey = {29, 29, 27, 255};
  Color yellow = {243, 216, 63, 255};
  // Initialization

  const int screenWidth = 1280;
  const int screenHeight = 900;

  InitWindow(screenWidth, screenHeight, "Space Invaders");

  // Load background texture after InitWindow
  Texture2D background = LoadTexture("Graphics/background.png");
  if (background.id == 0)
  {
    TraceLog(LOG_ERROR, "Failed to load background texture");
  }

  GameScreen currentScreen = LOGO;
  SetTargetFPS(60);
  int framesCounter = 0;
  Game game;

  // Main game loop
  while (!WindowShouldClose())
  {
    // Update
    switch (currentScreen)
    {
    case LOGO:
    {
      framesCounter++;
      if (framesCounter > 120) // 2 seconds at 60fps
      {
        currentScreen = TITLE;
        framesCounter = 0;
      }
    }
    break;

    case TITLE:
    {
      if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))
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

    // Draw
    BeginDrawing();
    ClearBackground(grey);

    switch (currentScreen)
    {
    case LOGO:
    {
      DrawText("LOADING...", screenWidth / 2 - MeasureText("LOADING...", 40) / 2,
               screenHeight / 2 - 40, 40, WHITE);
    }
    break;

    case TITLE:
    {
      if (background.id != 0)
      {
        DrawTexture(background, 0, 0, WHITE);
      }
      DrawText("SPACE INVADERS", screenWidth / 2 - MeasureText("SPACE INVADERS", 60) / 2,
               screenHeight / 3, 60, WHITE);
      DrawText("PRESS ENTER or SPACE to START", screenWidth / 2 - MeasureText("PRESS ENTER or SPACE to START", 20) / 2,
               screenHeight / 2 + 60, 20, WHITE);
    }
    break;

    case GAMEPLAY:
    {
      float margin = 40.0f; // Space from screen edges
      float rectWidth = (float)screenWidth - (2 * margin);
      float rectHeight = (float)screenHeight - (2 * margin);

      // Draw rounded rectangle border
      DrawRectangleRoundedLines(
          (Rectangle){
              margin,    // x position
              margin,    // y position
              rectWidth, // width
              rectHeight // height
          },
          0.1f, // roundness (0.0f to 1.0f)
          30,   // segments (higher = smoother)
          3.0f, // thickness
          yellow);
      game.Draw();
    }
    break;

    default:
      break;
    }

    EndDrawing();
  }

  // De-Initialization
  UnloadTexture(background);
  CloseWindow();

  return 0;
}