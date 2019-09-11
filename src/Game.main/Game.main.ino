
/* Use Pin A4 for SDA, A5 for SCL and use 3.3V for VCC power
 * Hetha: By DPigeon on GitHub
 */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "World.h"
#include "GameInterface.h"
#include "Player.h"

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
const int Button_Pin = 7; // digital ping connected to button
bool pressedJoystick = false;
bool startSelected = true;

/* Gameplay Global Variables */
const int maxX = 127;
const int maxY = 63;

World world;
GameInterface gameUI;
Player player;

int prevMoveX = 63, posX = 63; // Initial player position
int prevMoveY = 33, posY = 33;

void setup() {
  // Hardware Setup
  pinMode(buzzer, OUTPUT);
  pinMode(SW_Pin, OUTPUT);
  pinMode(Button_Pin, INPUT);
  digitalWrite(SW_Pin, HIGH);
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64 (mine)
    Serial.println(F("SSD1306 allocation failed."));
    for(;;); // Loop forever
  }
  display.display(); // Display logo of Adafruits at beginning
  // Loading 
  world.SetGameState(LOADING);
  world.LoadEnemies();
  delay(1000); // Pause for 1 second
  display.clearDisplay();
}

void loop() {
  float time = millis(); // Time since program started
  float dt = time / 1000;
  if (pressedJoystick && startSelected) {
    world.Update(dt);
    world.Draw();
  } else {
    gameUI.Introduction();
  }
}
