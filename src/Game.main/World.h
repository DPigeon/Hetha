#pragma once

#include "Enemy.h"

class World
{
  private:
    const static int levels = 10;
    const static int numEnemy = 1;
    int currentNumEnemy = 0;
    static World* instance; 
    Enemy* enemies[numEnemy];
  public:
    World();
    static World* GetInstance();
    void Draw();
    void LoadEnemies();
    void DetectCollision();
    void RemoveEnemy(int index);
    ~World();
};
