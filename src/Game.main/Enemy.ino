
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
    player.IncrementSize(); // Size increases to become harder
    LosingHealthSound();
    // Reset enemy
    ePosX = 0;
    ePosY = 0;
  } 
  else 
    display.drawCircle(ePosX, ePosY, enemySize, WHITE);
}

void Enemy::LosingHealthSound() {
  tone(buzzer, healthSound);
  delay(200);
  noTone(buzzer);
}

Enemy::~Enemy() {
}
