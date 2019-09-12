
#include "World.h"
#include "Player.h"
#include "Enemy.h"
#include "Projectile.h"

World* World::instance;
const int projectileNum = 10;
Projectile* projectileList[projectileNum];

World::World() {
  instance = this;
}

World* World::GetInstance() {
  return instance;
}

void World::Update(float dt) {

  // Projectiles
  if (digitalRead(Button_Pin) == 1 && currentProjectileNum < projectileNum) {
    Projectile* projectile = new Projectile(posX, posY, 1);
      projectileList[currentProjectileNum] = projectile;
      currentProjectileNum++;
  }
  if (GetGameState() == 2) { // We make sure to only draw the projectiles in the running state
    for (int i = 0; i < currentProjectileNum; i++) {
        projectileList[i]->Update(dt);
    }
  }

if (dt >= timeLevel[currentLevel - 1] && dt <= timeLevel[currentLevel - 1] + levelDelay) {
  // Interface should stay there for 4 seconds, but does not
    gameUI.LevelUp(currentLevel);
  }

  // Levels
  if (dt >= timeLevel[currentLevel - 1]) {
    LevelUp();
  }
}

void World::Draw() {
  SetGameState(RUNNING);
  int valueX = analogRead(X_Pin); /* X goes from 1023 to 0 left to right */
  int valueY = analogRead(Y_Pin); /* Y goes from 1023 to 0 down to up */
  int newX = map(valueX, 1023, 0, 0, maxX); /* new X goes from 0 to 128 */
  int newY = map(valueY, 1023, 0, maxY, 0); /* new Y goes from 0 to 64 */
  if (digitalRead(SW_Pin) != 1)
     display.drawPixel(-1, -1, WHITE);
  else {
     player.PlayerMovement(newX, newY); // Player controls
  }

  /* Draw Projectiles */
  if (GetGameState() == 2) { // We make sure to only draw the projectiles in the running state
    for (int i = 0; i < currentProjectileNum; i++) {
        projectileList[i]->Draw();
        projectileList[i]->DeleteOutOfMap();
    }
  }

  /* Draw Enemies */
  if (currentNumEnemy > 0) {
    for (int i = 0; i < numEnemy; i++) {
       enemies[i]->SpawnEnemy();
    }
  }
  // Draw Upcoming Enemies by Loading more
  if (currentNumEnemy == 0) {
    LoadEnemies(); // Will add some more enemies depending on what level we are in for difficulty
  }

  DetectProjectileEnemyCollision();
  //DetectEnemiesCollision();
    
  display.display();
  display.clearDisplay();
}

void World::LoadEnemies() {
  for (int i = 0; i < numEnemy; i++) {
    Enemy* enemy = new Enemy(random(0, 127), 0, random(1, 4), 1);
    enemies[i] = enemy;
    currentNumEnemy++;
  }
}

void World::DetectProjectileEnemyCollision() {
  for (int i = 0; i < currentProjectileNum; i++) {
    for (int j = 0; j < currentNumEnemy; j++) {
      if (projectileList[i]->GetPositionX() == enemies[j]->GetPositionX() && projectileList[i]->GetPositionX() == enemies[j]->GetPositionX()) {
        enemies[i]->DefeatedSound();
        RemoveProjectile(i);
        RemoveEnemy(j);
        delete projectileList[i];
        delete enemies[j];
      }
    }
  }
}

void World::DetectEnemiesCollision() {
  for (int i = 0; i < currentNumEnemy - 1; i++) {
    for (int j = i + 1; j < currentNumEnemy; j++) {
      if (enemies[i]->GetPositionX() == enemies[j]->GetPositionX()  && enemies[i]->GetPositionY() == enemies[j]->GetPositionY()) {
        RemoveEnemy(i);
        RemoveEnemy(j);
        delete enemies[i];
        delete enemies[j];
      }
    }
  }
}

void World::RemoveEnemy(int index) {
  for (int i = index; i < currentNumEnemy; i++) {
    enemies[i] = enemies[i + 1];
  }
  currentNumEnemy--;
}

void World::RemoveProjectile(int index) {
  for (int i = index; i < currentProjectileNum; ++i) {
    projectileList[i] = projectileList[i + 1];
  }
  currentProjectileNum--;
}

void World::LevelUp() {
  currentLevel++;
  SetGameState(LEVELUP);
  SetNewEnemySpeed(currentLevel);
}

void World::SetLevel(int level) {
  // When gameover, reset
  currentLevel = level;
  SetNewEnemySpeed(level);
}

int World::GetLevel() {
  return currentLevel;
}

int World::GetLevels() {
  return levels;
}

void World::SetGameState(GameState state) {
  GetInstance()->gameState = state;
}

void World::SetNewEnemySpeed(int speedLevel) {
  for (int i = 0; i < numEnemy; i++) {
    enemies[i]->SetSpeed(speedLevel);
  }
}

GameState World::GetGameState() {
  return GetInstance()->gameState;
}
World::~World() {
  delete [] enemies;
  delete [] projectileList;
}
