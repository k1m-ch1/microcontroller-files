#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define INTERRUPT_PIN D8

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#define FPS 30

char buffer[1024];

volatile unsigned long long count = 0;

void IRAM_ATTR isr(){
  count++;
}

void setup(){
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(D8), isr, RISING);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.clearDisplay();
  display.setTextSize(1);      // Normal 1X pixel scale
  display.setCursor(0, 0);     // Start at top-left corner
  display.setTextColor(WHITE); // Draw white pixels
  display.display();           // Show the text
}

void loop(){
  sprintf(buffer, "Count: %llu", count);
  Serial.println(buffer);
  display.clearDisplay();
  display.setCursor(0, 0);     // Start at top-left corner
  display.println(buffer);
  display.display();           // Show the text
  delay(1000/30);
}
