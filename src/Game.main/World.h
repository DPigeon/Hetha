#pragma once

#include "Enemy.h"

class World
{
  private:
    const static int numEnemy = 5;
    static World* instance; 
    Enemy* enemies[numEnemy];
  public:
    World();
    static World* GetInstance();
    void Draw();
    void LoadEnemies();
    void GenerateEnemies();
    ~World();
};
