
class Enemy {  
  public:
    void generateArmy() {
      //int randomDelay = random(500, 2000); // in milliseconds, in between 0.5 and 2 seconds
      //delay(5000);
      spawnEnemy();
    }
    
    void spawnEnemy() {
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
        playerSize++; // Size increases to become harder
        losingHealthSound();
        // Reset enemy
        ePosX = 0;
        ePosY = 0;
      } 
      else 
        display.drawCircle(ePosX, ePosY, enemySize, WHITE);
    }

    void losingHealthSound() {
      tone(buzzer, 100000);
      delay(200);
      noTone(buzzer);
    }

    ~Enemy() {
    }
};
