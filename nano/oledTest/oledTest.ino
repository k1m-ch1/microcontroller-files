#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1      // No reset pin

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char msg[50];

void oledPrint(char msg[]){
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);
  display.print(msg);
  display.display();
}

void setup() {
    Wire.begin();
    if (!display.begin(0x3C, true)) {
        Serial.println("OLED allocation failed");
        while (1);
    }
}

void loop() {
  sprintf(msg, "hello %lu", millis());
  oledPrint(msg);
}
