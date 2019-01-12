
/* Use Pin A4 for SDA, A5 for SCL and use 3.3V for VCC power */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

int lcdArray[SCREEN_WIDTH][SCREEN_HEIGHT];
int prevLcdArray[SCREEN_WIDTH][SCREEN_HEIGHT];

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* Controller Variables */
const int SW_Pin = 2; // digital pin connected to switch output
const int X_Pin = 0; // analog pin connected to X output
const int Y_Pin = 1; // analog pin connected to Y output
bool pressedJoystick = false;
bool startSelected = true;

void setup() {
  pinMode(SW_Pin, OUTPUT);
  digitalWrite(SW_Pin, HIGH);
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64 (mine)
    Serial.println(F("SSD1306 allocation failed."));
    for(;;); // Loop forever
  }
  display.display(); // Display logo of Adafruits at beginning
  delay(1000); // Pause for 1 second
  display.clearDisplay();
}

void loop() {
  if (pressedJoystick && startSelected) 
    startGame();
  else 
    introduction();
}

void introduction() { // There are some electrical noises sometimes
  if (analogRead(Y_Pin) > 526) { // Selector goes down
    startSelected = false;
    pressedJoystick = false;
    menuIntro(startSelected); // Becomes selected at other
  } else if (analogRead(Y_Pin) < 524 ) { // Selector goes up
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

void spawnRandomDots(int controllerPosX, int controllerPosY) {
  int randomX = random(0, SCREEN_WIDTH);
  int randomY = random(0, SCREEN_HEIGHT);
  int randomDelay = random(100, 5000);
  do {
    display.drawCircle(randomX, randomY, 1, WHITE);
  } while (controllerPosX != SCREEN_WIDTH && controllerPosY != randomY);
}

void startGame() {
  int valueX = analogRead(X_Pin); /* X goes from 1023 to 0 left to right */
  int valueY = analogRead(Y_Pin); /* Y goes from 1023 to 0 down to up */
  int newX = map(valueX, 1023, 0, 0, 127); /* new X goes from 0 to 128 */
  int newY = map(valueY, 1023, 0, 63, 0); /* new Y goes from 0 to 64 */
  if (digitalRead(SW_Pin) != 1)
     display.drawPixel(-1, -1, WHITE);
  else 
     display.drawCircle(newX, newY, 3, WHITE);
  spawnRandomDots(newX, newY);
  display.display();
  display.clearDisplay();
}
