#define LED_PIN 2
#define DELAY_TIME 1000

void setup(){
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop(){
  digitalWrite(LED_PIN, HIGH);
  Serial.println("led is on");
  delay(DELAY_TIME);
  digitalWrite(LED_PIN, LOW);
  Serial.println("led is off");
  delay(DELAY_TIME);
} 
