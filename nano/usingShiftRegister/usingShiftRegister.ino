#define SER 6
#define RCLK 7
#define SRCLK 8

// 10 -> RCLK (latchPin)
// 11 -> SRCLK (clockPin)
// 12 -> SER (dataPin)

void setup(){
  pinMode(SER, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SRCLK, OUTPUT);
}

void loop(){
  for (byte i = 0; i < 256; i++){
    digitalWrite(RCLK, LOW);
    shiftOut(SER, SRCLK, MSBFIRST, i);
    digitalWrite(RCLK, HIGH);
    delay(500);
  }
}
