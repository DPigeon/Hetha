
/* Use Pin A4 for SDA, A5 for SCL and use 3.3V for VCC power
 * Hetha: By DPigeon on GitHub
 */

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

/* Buzzer Variable */
const int buzzer = 9; // digital pin connected to buzzer output

/* Controller Variables */
const int SW_Pin = 2; // digital pin connected to switch output
const int X_Pin = 0; // analog pin connected to X output
const int Y_Pin = 1; // analog pin connected to Y output
bool pressedJoystick = false;
bool startSelected = true;

/* Gameplay Variables */
const int maxX = 127;
const int maxY = 63;
int prevMoveX = 63, posX = 63;
int prevMoveY = 33, posY = 33;
int offset = 5;
int playerSize = 3;
int ePrevPosX = random(0, maxX), ePosX = random(0, maxX); // Spawn at top of screen
int ePrevPosY = 0, ePosY = 0;
int eOffset = 1; // Enemy Speed
int enemySize = random(1, 4);

void setup() {
  pinMode(buzzer, OUTPUT);
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
