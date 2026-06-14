#define DELAY_TIME 1000

void setup(){
  Serial.begin(115200);
}

void loop(){
  Serial.println("Hello world!");
  delay(DELAY_TIME);
}
