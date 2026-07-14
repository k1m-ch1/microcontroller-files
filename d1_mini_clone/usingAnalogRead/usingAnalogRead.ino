#define DELAY_TIME 1000

void setup(){
  pinMode(A0, INPUT);
  Serial.begin(115200);
}

void loop(){
  int val = analogRead(A0);
  Serial.print("analogRead value: ");
  Serial.println(val);
  delay(DELAY_TIME);
}
