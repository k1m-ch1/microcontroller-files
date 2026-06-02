#include <FastLED.h>

#define LED_PIN 9
#define NUM_LEDS 300
#define BRIGHTNESS 1
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define DELAY_TIME 500

CRGB leds[NUM_LEDS];

void setup(){
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Red;
  }
  FastLED.show();
}

void loop(){
  /*
  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Green;
  }
  delay(DELAY_TIME);
  FastLED.show();

  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Red;
  }
  delay(DELAY_TIME);
  FastLED.show();

  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB::Blue;
  }
  delay(DELAY_TIME);
  FastLED.show();
  */
}
