
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(int id, int x, int y, int eSize, int eSpeed) {
  id = id;
  ePosX, ePrevPosX = x;
  ePosY, ePrevPosY = y;
  enemySize = eSize;
  eOffset = eSpeed;
}

void Enemy::SpawnEnemy() {
  // posX, posY of player
  if (ePosX > posX) { // Go left
    ePosX = ePrevPosX - eOffset;
    ePrevPosX = ePosX;
  }
  if (ePosX < posX) { // Go right
    ePosX = ePrevPosX + eOffset;
    ePrevPosX = ePosX;
  }
  if (ePosY < posY) { // Go down
    ePosY = ePrevPosY + eOffset;
    ePrevPosY = ePosY;
  }
  if (ePosY > posY) { // Go up
    ePosY = ePrevPosY - eOffset;
    ePrevPosY = ePosY;
  }
  if (ePosX == posX && ePosY == posY) { // Collision between enemy and player
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

Enemy::~Enemy() {
}
