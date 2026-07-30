#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  // Initialize with the default I2C address 0x3C
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1X pixel scale
  display.setTextColor(WHITE); // Draw white pixels
  display.setCursor(10, 10);     // Start at top-left corner
  display.println(F("Hello, World!"));
  display.display();           // Show the text
}

void loop() {
  // Nothing to do here
}
