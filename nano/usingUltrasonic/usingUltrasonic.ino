#define TRIG_PIN 11
#define ECHO_PIN 12

#define SPEED_OF_SOUND 343 // speed of sound s in m/s
#define TIMEOUT 1000

void setup(){
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  // normally TRIP_PIN is low by default
  digitalWrite(TRIG_PIN, LOW);
}

void loop(){
  // now pull it high for 10 microseconds
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // now wait for response
  while(!digitalRead(ECHO_PIN)){
  }
  unsigned long start = micros();
  while(digitalRead(ECHO_PIN)){
  }
  unsigned long responseTime = micros() - start;
  float distanceToObstacle = (SPEED_OF_SOUND * responseTime) / 20000.0f;
  Serial.println(distanceToObstacle);
  delay(1000);
}
