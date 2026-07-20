#include <SoftwareSerial.h>

#define RX_PIN D2
#define TX_PIN D3

SoftwareSerial mySerial(RX_PIN, TX_PIN);

void setup(){
  Serial.begin(115200);
  mySerial.begin(115200);
}

void loop(){
  while(Serial.available()){
    mySerial.write(Serial.read());
  }
  while(mySerial.available()){
    Serial.write(mySerial.read());
  }
}


