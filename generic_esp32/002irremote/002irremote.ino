#include <IRremote.h>

#define RECV_PIN 23

void setup() {
  Serial.begin(115200);
  // Start the receiver and enable feedback LED if available
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Receiver Ready. Press a button on your remote.");
}

void loop() {
  // Check if a new signal has been received and decoded
  if (IrReceiver.decode()) {
    Serial.print("Received Hex Code: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    
    // Enable receiving the next value
    IrReceiver.resume();
  }
}
