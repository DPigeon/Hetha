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
    int healthSound = 100000;
  public:
    Enemy(int x, int y, int eSize, int eSpeed);
    void SpawnEnemy();
    void LosingHealthSound();
    int GetPositionX();
    int GetPositionY();
    int GetSize();
    int GetSpeed();
    void SetSpeed(int s);
    ~Enemy();
};
