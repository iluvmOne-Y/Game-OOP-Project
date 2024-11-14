#include "aliens.h"
Texture2D Alien::alienImage[3] = {};
Alien::Alien(int type, Vector2 position)
{
    this->type = type;
    this->position = position;
    if (alienImage[type - 1].id == 0)
    {

        switch (type)
        {
        case 1:
            alienImage[0] = LoadTexture("Graphics/alien_1.png");
            break;
        case 2:

            alienImage[1] = LoadTexture("Graphics/alien_2.png");
            break;
        case 3:
            alienImage[2] = LoadTexture("Graphics/alien_3.png");
            break;

        default:
            alienImage[0] = LoadTexture("Graphics/alien_1.png");
            break;
        }
    }
}
void Alien::Draw()
{
    DrawTextureV(alienImage[type - 1], position, WHITE);
}

void Alien::UnloadImage()
{
    for (int i = 0; i < 4; i++)
    {
        UnloadTexture(alienImage[i]);
    }
}
Rectangle Alien::GetRectangle()
{
    return {position.x, position.y, (float)alienImage[type - 1].width, (float)alienImage[type - 1].height};
}
int Alien::GetType()
{
    return type;
}
void Alien::Update(int direction)
{
    position.x += direction;
}