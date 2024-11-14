#pragma once
#include <raylib-cpp.hpp>

class Alien
{
public:
    Alien(int type, Vector2 position);
    void Update(int direction);
    int GetType();
    void Draw();
    static void UnloadImage();
    static Texture2D alienImage[3];
    Rectangle GetRectangle();
    int type;
    Vector2 position;
};