#include "World.h"

World* World::instance;

World::World() {
  instance = this;
}
World* World::GetInstance() {
  return instance;
}
void World::addEnemy(Enemy* enemy) {
  for (int i = 0; i < numEnemy; i++) {
    Enemy* enemy = new Enemy();
    enemies[i] = enemy;
  }
}

World::~World() {
}
