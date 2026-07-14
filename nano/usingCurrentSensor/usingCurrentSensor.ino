
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1      // No reset pin

#define DELAY_TIME 100

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

char msg[50];
char floatBuffer[10];
float maxCurrent = 0;

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
    pinMode(A0, INPUT);
    Serial.begin(115200);
}

void loop() {
  oledPrint(msg);
  int val = analogRead(A0);
  //185 mV/A for 5A, 100 mV/A for 20A, and 66 mV/A for 30A
  float voltage = (val/1024.0f)*5.0f;
  float current = (voltage - 2.5)/0.066f;
  dtostrf(current, 6, 2, floatBuffer);
  sprintf(msg, "Current: %s\r\n", floatBuffer);
  Serial.print(msg);
  oledPrint(msg);
  delay(DELAY_TIME);
}
