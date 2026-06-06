const int latchPin = 10;
const int clockPin = 11;
const int dataPin = 12;

void setup(){
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop(){
  for (uint8_t i = 0; i < 256; i++){
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, i);
    digitalWrite(latchPin, HIGH);
    digitalWrite(latchPin, LOW);
    delay(500);
  }
}
