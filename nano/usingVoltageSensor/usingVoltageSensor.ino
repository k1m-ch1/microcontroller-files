
#define IN_PIN A0


void setup(){
  Serial.begin(115200);
  pinMode(IN_PIN, INPUT);
}

void loop(){
  int value = analogRead(IN_PIN);
  float voltage = (value/1024.0f)*25.0f;
  Serial.print("Voltage read: ");
  Serial.println(voltage);
  delay(1000);
}
