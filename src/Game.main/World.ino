
#include "World.h"
#include "Player.h"
#include "Enemy.h"

World* World::instance;

World::World() {
  instance = this;
}

World* World::GetInstance() {
  return instance;
}

void World::Draw() {
  int valueX = analogRead(X_Pin); /* X goes from 1023 to 0 left to right */
  int valueY = analogRead(Y_Pin); /* Y goes from 1023 to 0 down to up */
  int newX = map(valueX, 1023, 0, 0, maxX); /* new X goes from 0 to 128 */
  int newY = map(valueY, 1023, 0, maxY, 0); /* new Y goes from 0 to 64 */
  if (digitalRead(SW_Pin) != 1)
     display.drawPixel(-1, -1, WHITE);
  else {
     player.PlayerMovement(newX, newY); // Player controls
  }
  
  for (int i = 0; i < numEnemy; i++) {
    enemies[i]->SpawnEnemy();
  }

  //DetectCollision();
  
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

void World::DetectCollision() {
  for (int i = 0; i < currentNumEnemy - 1; i++) {
    for (int j = i + 1; j < currentNumEnemy; j++) {
      if (enemies[i]->GetPositionX() == enemies[j]->GetPositionX()  && enemies[i]->GetPositionY() == enemies[j]->GetPositionY()) {
        Serial.print(enemies[i]->GetPositionX());
        RemoveEnemy(i);
        delete enemies[i];
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

void World::LevelUp() {
  currentLevel++;
}

void World::SetLevel(int level) {
  currentLevel = level;
}

int World::GetLevel() {
  return currentLevel;
}

int World::GetLevels() {
  return levels;
}

void World::SetNewEnemySpeed(int speedLevel) {
  for (int i = 0; i < numEnemy; i++) {
    enemies[i]->SetSpeed(speedLevel);
  }
}

World::~World() {
  delete enemies;
}
