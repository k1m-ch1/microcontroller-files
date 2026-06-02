#include <avr/io.h>
#include <stdint.h>

#define DDR DDRD
#define P PD6
#define PORT PORTD
#define NUM_OF_LED 100

const uint8_t PIN_MASK = 1 << P;

static inline void sendBit(uint8_t mask) {
  // assume that mask is correctly, either 0x00 or 0xff
  PORT = ((PORT & (~PIN_MASK)) | (PIN_MASK & mask));
}

static inline void sendByte(uint8_t byteToSend) {
  // i belive, we send MSB (please compiler... unroll loop for me...)
  sendBit(-((byteToSend >> 7) & 1));
  sendBit(-((byteToSend >> 6) & 1));
  sendBit(-((byteToSend >> 5) & 1));
  sendBit(-((byteToSend >> 4) & 1));
  sendBit(-((byteToSend >> 3) & 1));
  sendBit(-((byteToSend >> 2) & 1));
  sendBit(-((byteToSend >> 1) & 1));
  sendBit(-((byteToSend >> 0) & 1));
}

struct pixel {
  uint8_t red;
  uint8_t blue;
  uint8_t green;
};

int main() {
  // toggle it as output

  DDR |= 1 << P;

  uint8_t byteArray[5];
  for (int i = 0; i < 5; i++) {
    byteArray[i] = 0b10101010;
  }

  uint8_t byteToSend = 0b10101010;

  while (1) {
    for (int i = 0; i < 5; i++) {
      sendByte(byteArray[i]);
    }
  }
  return 0;
}
