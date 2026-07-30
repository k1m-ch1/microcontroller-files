#define INPUT_PIN D8
void setup(){
  pinMode(INPUT_PIN, INPUT);
  Serial.begin(115200);
}

void loop(){
  Serial.println(digitalRead(INPUT_PIN));
}
