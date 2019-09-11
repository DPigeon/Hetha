#pragma once

class Projectile
{
  private:
    int pPosX;
    int pPosY;
    int velocityX;
    int velocityY;
    int pSize = 1;
  public:
    Projectile(int x, int y, int velocity);
    Draw();
    Update(float dt);
    DeleteOutOfMap();
    SetPosition(int x, int y);
    SetVelocity(int vX, int vY);
    ~Projectile();
};
