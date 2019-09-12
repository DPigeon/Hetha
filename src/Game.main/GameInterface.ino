
#include "GameInterface.h"
#include "World.h"

void GameInterface::Introduction() { // There are some electrical noises sometimes
  World* world = World::GetInstance();
  world->SetGameState(MENU);
  if (analogRead(Y_Pin) < 1023 && analogRead(Y_Pin) > 700) { // Selector goes down
    SelectionSound();
    startSelected = false;
    pressedJoystick = false;
    MenuIntro(startSelected); // Becomes selected at other
  } else if (analogRead(Y_Pin) < 400 && analogRead(Y_Pin) > 0) { // Selector goes up
    SelectionSound();
    startSelected = true;
    pressedJoystick = false;
    MenuIntro(startSelected); // Becomes selected at 'start'
  } else { // When controller at rest
    MenuIntro(startSelected);
    pressedJoystick = false;
  }
  if (digitalRead(SW_Pin) != 1)
    pressedJoystick = true;
  display.display();
}

void GameInterface::SelectionSound() {
  // Maybe play with volume with a resistor here ?
  tone(buzzer, uiSound);
  delay(200);
  noTone(buzzer);
}

void GameInterface::MenuIntro(bool textColor) {
  if (textColor == true) {
    display.clearDisplay();
    display.setTextSize(1);             
    display.setTextColor(WHITE);
    display.setCursor(35, 10);             
    display.println("Hetha Game");
    display.setCursor(50, 30);
    display.setTextColor(BLACK, WHITE); 
    display.println("Start");
    display.setTextColor(WHITE);
    display.setCursor(50, 50); 
    display.println("About");
  } else {
    display.clearDisplay();
    display.setTextSize(1);             
    display.setTextColor(WHITE);
    display.setCursor(35, 10);             
    display.println("Hetha Game");
    display.setTextColor(WHITE);
    display.setCursor(50, 30); 
    display.println("Start");
    display.setTextColor(BLACK, WHITE);
    display.setCursor(50, 50); 
    display.println("About");
  }
}

void GameInterface::LevelUp(int level) {
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(WHITE);
  display.setCursor(35, 10);             
  display.println("LEVEL UP!");
  display.setCursor(47, 30);
  display.setTextColor(BLACK, WHITE); 
  display.println("Hetha");
  display.setCursor(43, 50);
  display.setTextColor(BLACK, WHITE); 
  display.println("Level" + level);
}

void GameInterface::GameOver() {
  World* world = World::GetInstance();
  world->SetLevel(1); // Reset level back to 1
  world->SetGameState(GAMEOVER);
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(WHITE);
  display.setCursor(35, 10);             
  display.println("GAME OVER");
  display.setCursor(47, 30);
  display.setTextColor(BLACK, WHITE); 
  display.println("Move to");
  display.setCursor(43, 50);
  display.setTextColor(BLACK, WHITE); 
  display.println("continue");
}

GameInterface::~GameInterface() {
}
