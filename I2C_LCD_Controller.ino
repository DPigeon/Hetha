
/* Use Pin A4 for SDA, A5 for SCL and use 3.3V for VCC power */

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/* Controller Variables */
const int SW_Pin = 2; // digital pin connected to switch output
const int X_Pin = 0; // analog pin connected to X output
const int Y_Pin = 1; // analog pin connected to Y output
boolean pressedJoystick = false;

void setup() {
  pinMode(SW_Pin, OUTPUT);
  digitalWrite(SW_Pin, HIGH);
  Serial.begin(9600);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64 (mine)
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();
  introduction();
}

void loop() {
  if (pressedJoystick)
    controlDot();
  else
    introduction();
}

void introduction() {
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(WHITE);       
  display.setCursor(10, 10);             
  display.println(F("Welcome to Hexa !"));

  display.setCursor(20, 20); 
  display.println("- Version 1.0");

  display.setCursor(0, 40); 
  display.println("---> Press Joystick  to begin...");
  if (digitalRead(SW_Pin) != 1)
    pressedJoystick = true;
  display.display();
}

void controlDot() {
  int valueX = analogRead(X_Pin);
  int valueY = analogRead(Y_Pin);
  /* X goes from 1023 to 0 left to right */
  /* Y goes from 1023 to 0 down to up */
  
  /* X goes from 0 to 128 */
  /* Y goes from 0 to 64 */
  int newX = map(valueX, 1023, 0, 0, 127);
  int newY = map(valueY, 1023, 0, 63, 0);
  if (digitalRead(SW_Pin) != 1)
     display.drawPixel(-1, -1, WHITE);
  else
     display.drawPixel(newX, newY, WHITE);
  display.display();
  display.clearDisplay();
}
