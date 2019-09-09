
#include "Player.h"

void Player::PlayerMovement(int x, int y) { 
  if (x < 63 && posX >= boundary) { // Go left
    posX = prevMoveX - offset;
    prevMoveX = posX;
  }
  if (x > 63 && posX <= maxX - boundary) { // Go right
    posX = prevMoveX + offset;
    prevMoveX = posX;
  }
  if (y > 33 && posY <= maxY - boundary) { // Go down
    posY = prevMoveY + offset;
    prevMoveY = posY;
  }
  if (y < 33 && posY >= boundary) { // Go up
    posY = prevMoveY - offset;
    prevMoveY = posY;
  }
  display.fillCircle(posX, posY, playerSize, WHITE);
}

void Player::IncrementSize() {
  playerSize++;
}

int Player::GetSize() {
  return playerSize;
}

Player::~Player() {
}
