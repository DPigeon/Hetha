#pragma once

class Player
{
  private:
    int offset = 5; // player speed
    int playerSize = 3;
    const int boundary = 4;
  public:
    void PlayerMovement(int x, int y);
    void IncrementSize();
    int GetSize();
    ~Player();
};
