
// this is the Data Direction Register for our pin
#define LED_DDR DDRD
#define LED_PORT PORTD
#define LED_PIN PD6
// LED_PIN is defined with respect to the port (for pin 9, it's PORT B, PB1)

/*
|cycles|delay|
|---|---|
|0|0.0|
|1|62.5|
|2|125.0|
|3|187.5|
|4|250.0|
|5|312.5|
|6|375.0|
|7|437.5|
|8|500.0|
|9|562.5|
|10|625.0|
|11|687.5|
|12|750.0|
|13|812.5|
|14|875.0|
|15|937.5|
|16|1000.0|
|17|1062.5|
|18|1125.0|
|19|1187.5|
*/

/*
 * 0 means: $400 \pm 150 ns$ HIGH, $850 \pm 150 ns$ LOW
 * 1 means: $800 \pm 150 ns$ HIGH, $450 \pm 150 ns$ LOW
 * Reset: over $50 000 ns$ of LOW
*/

void sendResetCode(){
  LED_PORT &= ~(1 << LED_PIN);
  // this is already at least 2 cycles, so already 125ns has passed
  int start = millis();
  while(millis() - start < 60){
  }
}



void send0(){
  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");
}

void send1(){
  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
}

template<bool bit>
inline void sendBit(){
  if constexpr (bit){
    LED_PORT |= (1 << LED_PIN);
    __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
    LED_PORT &= ~(1 << LED_PIN);
  } else {
    LED_PORT |= (1 << LED_PIN);
    __asm__("nop\nnop\nnop\nnop\n");
    LED_PORT &= ~(1 << LED_PIN);
    __asm__("nop\nnop\nnop\nnop\nnop\n");

  }
}

void setup(){
  // equivalent to pinMode
  LED_DDR |= 1 << LED_PIN;
  // send a reset signal, which is at least 50 microseconds
  sendResetCode();
}

void loop(){
  noInterrupts();
  /*
  uint_32 color = 0xFF0000;
  uint_8 redByte = (color >> 4) & 0b11;
  uint_8 blueByte = (color >> 2) & 0b11;
  uint_8 greenByte = (color >> 0) & 0b11;
  */
  // send it in the order of GRB

 LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);

  LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);

 LED_PORT |= (1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\n");
  LED_PORT &= ~(1 << LED_PIN);
  __asm__("nop\nnop\nnop\nnop\nnop\n");

 // since a function call adds so much overhead, this is like pretty much imposssible to do without assembly, or without writing really shit code
 
  interrupts();
  delay(500);
}
