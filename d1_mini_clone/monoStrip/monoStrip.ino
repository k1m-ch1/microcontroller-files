#define R_PIN D6
#define G_PIN D7
#define B_PIN D8

#define DELAY_TIME 1000

void setup(){
  Serial.begin(115200);
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);

  digitalWrite(R_PIN, LOW);
  digitalWrite(G_PIN, LOW);
  digitalWrite(B_PIN, LOW);
  Serial.println("hello");
}

void loop(){
  digitalWrite(R_PIN, HIGH);
  Serial.println("setting red high");
  delay(DELAY_TIME);
  digitalWrite(R_PIN, LOW);

  digitalWrite(G_PIN, HIGH);
  Serial.println("setting green high");
  delay(DELAY_TIME);
  digitalWrite(G_PIN, LOW);

  digitalWrite(B_PIN, HIGH);
  Serial.println("setting blue high");
  delay(DELAY_TIME);
  digitalWrite(B_PIN, LOW);
}
