#pragma once

class Enemy
{
  private:
    int ePrevPosX; // Spawn at top of screen    
    int ePosX;
    int ePrevPosY;
    int ePosY;
    int eOffset; // Enemy Speed
    int enemySize;
    int healthSound = 3000;
    int deadSound = 1000;
  public:
    Enemy(int x, int y, int eSize, int eSpeed);
    void SpawnEnemy();
    void LosingHealthSound();
    void DefeatedSound();
    int GetPositionX();
    int GetPositionY();
    int GetSize();
    int GetSpeed();
    void SetSpeed(int s);
    ~Enemy();
};
