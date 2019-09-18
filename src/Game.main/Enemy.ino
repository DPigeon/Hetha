
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(int x, int y, int eSize, int eSpeed) {
  ePosX, ePrevPosX = x;
  ePosY, ePrevPosY = y;
  enemySize = eSize;
  eOffset = eSpeed;
}

void Enemy::SpawnEnemy() {
  // posX, posY of player
  int enemyOffset = 0;
  if (ePosX > posX) { // Go left
    enemyOffset = - eOffset;
    ePosX = ePrevPosX + enemyOffset;
    ePrevPosX = ePosX;
  }
  if (ePosX < posX) { // Go right
    enemyOffset = eOffset;
    ePosX = ePrevPosX + enemyOffset;
    ePrevPosX = ePosX;
  }
  if (ePosY < posY) { // Go down
    enemyOffset = eOffset;
    ePosY = ePrevPosY + enemyOffset;
    ePrevPosY = ePosY;
  }
  if (ePosY > posY) { // Go up
    enemyOffset = - eOffset;
    ePosY = ePrevPosY + enemyOffset;
    ePrevPosY = ePosY;
  }
  if (ePosX + enemyOffset == posX && ePosY + enemyOffset == posY) { // Collision between enemy and player
    //player.IncrementSize(); // Size increases to become harder
    LosingHealthSound();
    gameUI.GameOver();
  } 
  else 
    display.drawCircle(ePosX, ePosY, enemySize, WHITE);
}

void Enemy::LosingHealthSound() {
  tone(buzzer, healthSound);
  delay(200);
  noTone(buzzer);
}

void Enemy::DefeatedSound() {
  tone(buzzer, deadSound);
  delay(200);
  noTone(buzzer);
}

int Enemy::GetPositionX() {
  return ePosX;
}

int Enemy::GetPositionY() {
  return ePosY;
}

int Enemy::GetSize() {
  return enemySize;
}

int Enemy::GetSpeed() {
  return eOffset;
}

void Enemy::SetSpeed(int s) {
  eOffset = s;
}

Enemy::~Enemy() {
}
