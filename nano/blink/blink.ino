
#define DELAY_TIME 1000
#define LED_PIN 6

void setup(){
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop(){
  digitalWrite(LED_PIN, HIGH);
  delay(DELAY_TIME);
  Serial.println("LED is high!");
  digitalWrite(LED_PIN, LOW);
  delay(DELAY_TIME);
  Serial.println("LED is low!"); }
