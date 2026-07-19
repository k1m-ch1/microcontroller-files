#include "pins_arduino.h"
#include <Arduino.h>

int main() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  return 0;
}
