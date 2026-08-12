#include <Arduino.h>

void setup() { pinMode(PC13, OUTPUT); }

void loop() {
  digitalWrite(PC13, LOW); // LED ON (Blue Pill is active low)
  delay(1000);

  digitalWrite(PC13, HIGH); // LED OFF
  delay(1000);
}
