#include <SoftwareSerial.h>

#define RX_PIN D2
#define TX_PIN D3

SoftwareSerial mySerial(RX_PIN, TX_PIN);

void setup(){
  Serial.begin(115200);
  mySerial.begin(115200);
  Serial.println("G28");
}

void loop(){

}
