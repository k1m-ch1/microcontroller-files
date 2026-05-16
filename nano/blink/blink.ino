
#define DELAY_TIME 1000

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
}

void loop(){
  digitalWrite(LED_BUILTIN, HIGH);
  delay(DELAY_TIME);
  Serial.println("LED is high!");
  digitalWrite(LED_BUILTIN, LOW);
  delay(DELAY_TIME);
  Serial.println("LED is low!"); }
