#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <util/delay.h>

#define DDR DDRD
#define P PD6
#define PORT PORTD
#define NUM_OF_LED 300
#define DELAY_TIME 500

const uint8_t PIN_MASK = 1 << P;

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

static inline void sendBit(uint8_t mask) {
  // assume that mask is correctly, either 0x00 or 0xff

  /*
   * 0 means: $400 \pm 150 ns$ HIGH, $850 \pm 150 ns$ LOW
   * 1 means: $800 \pm 150 ns$ HIGH, $450 \pm 150 ns$ LOW
   * Reset: over $50 000 ns$ of LOW
   */

  // first toggle HIGH
  PORT |= PIN_MASK;
  // then toggle based on whether we want to send a 0 or a 1
  PORT = ((PORT & (~PIN_MASK)) | (PIN_MASK & mask));
  // 7 nops
  __asm__("nop\nnop\nnop\n");
  // then back low
  PORT &= ~PIN_MASK;
}

static inline void sendByte(uint8_t byteToSend) {
  // i belive, we send MSB (please compiler... unroll loop for me...)
  sendBit(-((byteToSend >> 7) & 1));
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\n");
  sendBit(-((byteToSend >> 6) & 1));
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\n");
  sendBit(-((byteToSend >> 5) & 1));
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\n");
  sendBit(-((byteToSend >> 4) & 1));
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\n");
  sendBit(-((byteToSend >> 3) & 1));
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\n");
  sendBit(-((byteToSend >> 2) & 1));
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\n");
  sendBit(-((byteToSend >> 1) & 1));
  __asm__("nop\nnop\nnop\nnop\nnop\nnop\n");
  sendBit(-((byteToSend >> 0) & 1));
}

struct pixel {
  uint8_t red;
  uint8_t blue;
  uint8_t green;
};

uint8_t *pixelToByteArray(struct pixel pixelArray[], unsigned int length) {
  uint8_t *byteArray = (uint8_t *)malloc(3 * length * sizeof(uint8_t));
  for (int i = 0; i < length; i++) {
    // send it in GRB order
    byteArray[3 * i] = pixelArray[i].green;
    byteArray[3 * i + 1] = pixelArray[i].red;
    byteArray[3 * i + 2] = pixelArray[i].blue;
  }
  return byteArray;
}

void sendData(uint8_t *byteArray, int length) {
  for (int i = 0; i < length; i++) {
    sendByte(byteArray[i]);
  }
}

int main() {
  // toggle it as output

  DDR |= 1 << P;

  struct pixel pixelArray[NUM_OF_LED];

  for (int i = 0; i < NUM_OF_LED; i++) {
    pixelArray[i].red = 0x00;
    pixelArray[i].green = 0x0f;
    pixelArray[i].blue = 0x0f;
  }
  uint8_t *byteArray = pixelToByteArray(pixelArray, NUM_OF_LED);
  while (1) {
    sendData(byteArray, NUM_OF_LED * 3);
    _delay_ms(DELAY_TIME);
  }
  return 0;
}
