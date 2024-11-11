#include "game.h"
#include "spaceship.h"

Game::Game()
{
  obstacles = createObstacles();
  aliens = createAliens();
  alienDirection = 2;
}
Game::~Game()
{
  Alien::UnloadImage();
}
void Game::Draw()
{
  spaceship.Draw();
  for (auto &Laser : spaceship.lasers)
  {
    Laser.Draw();
  }
  for (auto &obstacle : obstacles)
  {
    obstacle.Draw();
  }
  for (auto &alien : aliens)
  {
    alien.Draw();
  }
  DeleteInactiveLasers();
}
void Game::Update()
{
  for (auto &Laser : spaceship.lasers)
  {
    Laser.Update();
  }
  moveAliens();
}
void Game::HandleInput()
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
}

std::vector<Obstacle> Game::createObstacles()
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
}

std::vector<Alien> Game::createAliens()
{
  std::vector<Alien> aliens;
  for (int i = 0; i < 5; i++)
  {
    for (int j = 0; j < 15; j++)
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

      float x = 110 + j * 70;
      float y = 110 + i * 70;
      aliens.push_back(Alien(alienType, {x, y}));
    }
  }
  return aliens;
}
void Game::moveAliens()
{
  for (auto &Alien : aliens)
  {
    if (Alien.position.x + Alien.alienImage[Alien.type - 1].width > GetScreenWidth())
    {
      alienDirection = -2;
      moveAliensDown();
    }
    if (Alien.position.x < 0)
    {
      alienDirection = 2;
      moveAliensDown();
    }
    Alien.Update(alienDirection);
  }
}

void Game::moveAliensDown()
{
  for (auto &Alien : aliens)
  {
    Alien.position.y += 2;
  }
}
