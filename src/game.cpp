#include "game.h"
#include "spaceship.h"

Game::Game()
{

  InitGame();
}
Game::~Game()
{
  Alien::UnloadImage();
}
void Game::Draw()
{
  spaceship.Draw();
  for (auto &spaceshipLaser : spaceship.lasers)
  {
    spaceshipLaser.Draw();
  }
  for (auto &obstacle : obstacles)
  {
    obstacle.Draw();
  }
  for (auto &alien : aliens)
  {
    alien.Draw();
  }
  for (auto &alienLaser : alienLasers)
  {
    alienLaser.Draw();
  }
}
void Game::Update()
{
  if (run)
  {
    for (auto &Laser : spaceship.lasers)
    {
      Laser.Update();
    }
    MoveAliens();
    AliensShooter();
    for (auto &laser : alienLasers)
    {
      laser.Update();
    }

    DeleteInactiveLasers();

    // Check all collisions
    CheckForCollisions();
  }
  else
  {
    if (IsKeyDown(KEY_ENTER))
    {
      ResetGame();
      InitGame();
    }
  }
}

void Game::HandleInput()
{
  if (run)
  {
    if (IsKeyDown(KEY_LEFT))
    {
      spaceship.MoveLeft();
    }
    else if (IsKeyDown(KEY_RIGHT))
    {
      spaceship.MoveRight();
    }
    else if (IsKeyDown(KEY_SPACE))
    {
      spaceship.FireLaser();
    }
  }
}
void Game::DeleteInactiveLasers()
{
  for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
  {
    if (!it->active)
    {
      it = spaceship.lasers.erase(it);
    }
    else
    {
      it++;
    }
  }
  for (auto it = alienLasers.begin(); it != alienLasers.end();)
  {
    if (!it->active)
      it = alienLasers.erase(it);
    else
      ++it;
  }
}
std::vector<Obstacle> Game::createObstacles()
{
  float margin = 40.0f;
  float screenWidth = GetScreenWidth() - (2 * margin);
  float screenHeight = GetScreenHeight() - (2 * margin);

  int obstacleWidth = Obstacle::grid[0].size() * 3;

  // Position obstacles at 60% of screen height
  float obstacleY = margin + (screenHeight * 0.7f);

  // Calculate gap between obstacles
  float totalObstaclesWidth = obstacleWidth * 4;       // 4 obstacles
  float gap = (screenWidth - totalObstaclesWidth) / 5; // 5 gaps (including edges)

  for (int i = 0; i < 4; i++)
  {
    float offsetX = (i + 1) * gap + i * obstacleWidth;
    obstacles.push_back(Obstacle({offsetX, obstacleY}));
  }
  return obstacles;
}
/*std::vector<Obstacle> Game::createObstacles()
{
  int obstacleWidth = Obstacle::grid[0].size() * 3;
  float gap = (GetScreenWidth() - (4 * obstacleWidth)) / 5;
  float obstacleY = GetScreenHeight() - 300;
  for (int i = 0; i < 4; i++)
  {
    float offsetX = (i + 1) * gap + i * obstacleWidth;
    obstacles.push_back(Obstacle({offsetX, obstacleY}));
  }
  return obstacles;
}*/

std::vector<Alien> Game::createAliens()
{
  std::vector<Alien> aliens;
  float margin = 40.0f;
  float screenWidth = GetScreenWidth() - (2 * margin);

  const float ALIEN_SPACING_X = 50;  // Horizontal space between aliens
  const float ALIEN_SPACING_Y = 40;  // Vertical space between aliens
  const float START_X = margin + 50; // Starting X position
  const float START_Y = margin + 40;
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      int alienType;
      if (i == 0)
      {
        alienType = 3;
      }
      if (i == 1)
      {
        alienType = 2;
      }
      if (i > 2)
      {
        alienType = 1;
      }

      float x = START_X + j * ALIEN_SPACING_X;
      float y = START_Y + i * ALIEN_SPACING_Y;
      aliens.push_back(Alien(alienType, {x, y}));
    }
  }
  return aliens;
}
void Game::MoveAliens()
{
  float margin = 40.0f;
  for (auto &alien : aliens)
  {

    if (alien.position.x + alien.alienImage[alien.type - 1].width > GetScreenWidth() - margin)
    {
      aliensDirection = -1;
      MoveAliensDown();
    }
    if (alien.position.x < margin)
    {
      aliensDirection = 1;
      MoveAliensDown();
    }

    alien.Update(aliensDirection);
  }
}

void Game::CheckForCollisions()
{
  for (auto &laser : spaceship.lasers)
  {
    auto it = aliens.begin();
    while (it != aliens.end())
    {
      if (CheckCollisionRecs(it->GetRectangle(), laser.GetRectangle()))
      {
        it = aliens.erase(it);
        laser.active = false;
      }
      else
      {
        it++;
      }
    }

    for (auto &obstacle : obstacles)
    {

      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end())
      {
        if (CheckCollisionRecs(it->GetRectangle(), laser.GetRectangle()))
        {
          it = obstacle.blocks.erase(it);
          laser.active = false;
        }
        else
        {
          it++;
        }
      }
    }
  }
  for (auto &laser : alienLasers)
  {
    if (CheckCollisionRecs(spaceship.GetRectangle(), laser.GetRectangle()))
    {
      laser.active = false;
      lives--;
      if (lives == 0)
      {
        GameOver();
      }
    }
    for (auto &obstacle : obstacles)
    {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end())
      {
        if (CheckCollisionRecs(it->GetRectangle(), laser.GetRectangle()))
        {
          it = obstacle.blocks.erase(it);
          laser.active = false;
        }
        else
        {
          it++;
        }
      }
    }
  }
  for (auto &alien : aliens)
  {
    for (auto &obstacle : obstacles)
    {
      auto it = obstacle.blocks.begin();
      while (it != obstacle.blocks.end())
      {
        if (CheckCollisionRecs(it->GetRectangle(), alien.GetRectangle()))
        {
          it = obstacle.blocks.erase(it);
        }
        else
        {
          it++;
        }
      }
    }
    if (CheckCollisionRecs(spaceship.GetRectangle(), alien.GetRectangle()))
    {
      GameOver();
    }
  }
}

void Game::AliensShooter()
{
  double currentTime = GetTime();
  if (currentTime - timeAlienShooting >= timeAlienShootingInterval && !aliens.empty())
  {
    // Allow 2-3 aliens to shoot at once
    int shootersCount = GetRandomValue(1, 2);
    for (int i = 0; i < shootersCount; i++)
    {
      int randomIndex = GetRandomValue(0, aliens.size() - 1);
      Alien &alien = aliens[randomIndex];
      alienLasers.push_back(Laser({alien.position.x + alien.alienImage[alien.type - 1].width / 2,
                                   alien.position.y + alien.alienImage[alien.type - 1].height},
                                  6));
    }
    timeAlienShooting = GetTime();
  }
}

void Game::MoveAliensDown()
{
  for (auto &Alien : aliens)
  {
    Alien.position.y += 2;
  }
}

void Game::GameOver()
{
  run = false;
}

void Game::InitGame()
{
  float margin = 40.0f;
  float screenWidth = GetScreenWidth() - (2 * margin);
  float screenHeight = GetScreenHeight() - (2 * margin);

  // Initialize spaceship position at bottom center of screen
  float spaceshipX = margin + screenWidth / 2.0f - 32; // 32 is half the spaceship width
  float spaceshipY = GetScreenHeight() - margin - 200; // Adjust Y position to be above margin
  spaceship.position = {spaceshipX, spaceshipY};
  obstacles = createObstacles();
  aliens = createAliens();
  aliensDirection = 2;
  timeAlienShooting = 0;
  lives = 3;
  run = true;
}

void Game::ResetGame()
{
  spaceship.Reset();
  aliens.clear();
  alienLasers.clear();
  obstacles.clear();
}
