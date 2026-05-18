
#define PIN_DDR DDRD
#define PIN_PORT PORTD
#define PIN PD6

void setup(){
  // setup pin 6
  // according to https://electronoobs.com/images/Arduino/tut_130/Arduino_ports.jpg
  
  PIN_DDR |= (1 << PIN);
  while(true){
    PIN_PORT |= (1 << PIN);
    __asm__("nop\n");
    PIN_PORT &= ~(1 << PIN);
    __asm__("nop\n");
    PIN_PORT |= (1 << PIN);
    __asm__("nop\n");
    PIN_PORT &= ~(1 << PIN);
    __asm__("nop\n");
    PIN_PORT |= (1 << PIN);
    __asm__("nop\n");
    PIN_PORT &= ~(1 << PIN);
    delay(500);
  }
}

void loop(){
}
