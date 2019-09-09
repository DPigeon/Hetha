#pragma once

class Player
{
  private:
    const int boundary = 4;
  public:
    void playerMovement(int x, int y);
    ~Player();
};
