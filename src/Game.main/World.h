#pragma once

#include "Enemy.h"

enum GameState
{
  LOADING, // 0
  MENU,    // 1
  RUNNING, // 2
  LEVELUP, // 3
  GAMEOVER // 4
};

class World
{
  private:
    const static int levels = 10;
    float timeLevel [10] = {24, 48, 72, 96, 120, 144, 168, 192, 216, 240}; // 20 seconds for each levels (excluding levelUp interface delay)
    int currentLevel = 1;
    const float levelDelay = 4;
    const static int numEnemy = 1;
    int currentNumEnemy = 0;
    int currentProjectileNum = 0;
    static World* instance; 
    GameState gameState;
    Enemy* enemies[numEnemy];
  public:
    World();
    static World* GetInstance();
    void Update(float dt);
    void Draw();
    void LoadEnemies();
    void DetectCollision();
    void RemoveEnemy(int index);
    void RemoveProjectile();
    void LevelUp();
    void SetLevel(int level);
    int GetLevel();
    int GetLevels();
    void SetGameState(GameState state);
    void SetNewEnemySpeed(int speedLevel);
    GameState GetGameState();
    ~World();
};
