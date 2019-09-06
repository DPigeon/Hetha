
void selectionSound() {
  // Maybe play with volume with a resistor here ?
  tone(buzzer, 100);
  delay(200);
  noTone(buzzer);
}

void introduction() { // There are some electrical noises sometimes
  if (analogRead(Y_Pin) < 1023 && analogRead(Y_Pin) > 700) { // Selector goes down
    selectionSound();
    startSelected = false;
    pressedJoystick = false;
    menuIntro(startSelected); // Becomes selected at other
  } else if (analogRead(Y_Pin) < 400 && analogRead(Y_Pin) > 0) { // Selector goes up
    selectionSound();
    startSelected = true;
    pressedJoystick = false;
    menuIntro(startSelected); // Becomes selected at 'start'
  } else { // When controller at rest
    menuIntro(startSelected);
    pressedJoystick = false;
  }
  if (digitalRead(SW_Pin) != 1)
    pressedJoystick = true;
  display.display();
}

void menuIntro(bool textColor) {
  if (textColor == true) {
    display.clearDisplay();
    display.setTextSize(1);             
    display.setTextColor(WHITE);
    display.setCursor(35, 10);             
    display.println("Hetha Game!");
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
    display.println("Hetha Game!");
    display.setTextColor(WHITE);
    display.setCursor(50, 30); 
    display.println("Start");
    display.setTextColor(BLACK, WHITE);
    display.setCursor(50, 50); 
    display.println("About");
  }
}

void startGame() {
  int valueX = analogRead(X_Pin); /* X goes from 1023 to 0 left to right */
  int valueY = analogRead(Y_Pin); /* Y goes from 1023 to 0 down to up */
  int newX = map(valueX, 1023, 0, 0, maxX); /* new X goes from 0 to 128 */
  int newY = map(valueY, 1023, 0, maxY, 0); /* new Y goes from 0 to 64 */
  if (digitalRead(SW_Pin) != 1)
     display.drawPixel(-1, -1, WHITE);
  else {
     playerMovement(newX, newY); // Player controls
  }
  generateArmy(); // Generate Enemies
  display.display();
  display.clearDisplay();
}
