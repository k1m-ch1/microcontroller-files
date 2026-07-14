#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(115200);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
}

void loop(){
  Serial.print("Temperature: ");
  Serial.println(bmp.readTemperature());
  Serial.print("Pressure: ");
  Serial.println(bmp.readPressure());
  Serial.print("Altitude: ");
  Serial.println(bmp.readAltitude());
  Serial.print("Sea Level pressure: ");
  Serial.println(bmp.readSealevelPressure());
  delay(500);
}
