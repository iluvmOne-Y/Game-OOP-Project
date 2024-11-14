#include <raylib-cpp.hpp>
#include <vector>

class Laser
{
private:
  Vector2 position;
  int speed;

public:
  Laser(Vector2 position, int speed);
  void Draw();
  void Update();
  bool active;
  Rectangle GetRectangle();
};
