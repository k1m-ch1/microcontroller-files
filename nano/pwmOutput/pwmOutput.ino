
#define PIN 9

void setup(){
  pinMode(PIN, OUTPUT);
  Serial.begin(115200);
}

void loop(){
  if (Serial.available() > 0){
    int pwmCommand = Serial.parseInt();
    analogWrite(PIN, pwmCommand);
    Serial.println(pwmCommand);
  }
}
