Just for comparison:



without function overhead:

```c
#include <avr/io.h>

#define DDR DDRD
#define P PD6
#define PORT PORTD

int main() {
  // toggle it as output
  DDR |= 1 << P;

  while (1) {
    // let's see how fast i can toggle this
    PORT |= 1 << P;
    PORT &= ~(1 << P); 
  }
  return 0;
}
```

- HIGH: 126ns (2 cycles)
- LOW: 250ns (4 cycles)

With function overhead:

```c
#include <avr/io.h>

#define DDR DDRD
#define P PD6
#define PORT PORTD

void toggleOn() { PORT |= 1 << P; }

void toggleOff() { PORT &= ~(1 << P); }

int main() {
  // toggle it as output
  DDR |= 1 << P;

  while (1) {
    // let's see how fast i can toggle this
    toggleOn();
    toggleOff();
  }
  return 0;
}
```

- HIGH: 622ns (10 cycles)
- LOW: 753.665ns (12 cycles)

Ok, calling a function adds about 8 cycles, which is really bad. Let's use the `static inline` keyword now

```c
#include <avr/io.h>

#define DDR DDRD
#define P PD6
#define PORT PORTD

static inline void toggleOn() { PORT |= 1 << P; }

static inline void toggleOff() { PORT &= ~(1 << P); }

int main() {
  // toggle it as output
  DDR |= 1 << P;

  while (1) {
    // let's see how fast i can toggle this
    toggleOn();
    toggleOff();
  }
  return 0;
}
```

- HIGH: 126ns (2 cycles)
- LOW: 250ns (4 cycles)

ok... so function overhead is reduced... nice...

Using the bit mask method:

```c
#include <avr/io.h>
#include <stdint.h>

#define DDR DDRD
#define P PD6
#define PORT PORTD

const uint8_t PIN_MASK = 1 << P;

static inline void sendBit(uint8_t mask) {
  // assume that mask is correctly, either 0x00 or 0xff
  PORT = ((PORT & (~PIN_MASK)) | (PIN_MASK & mask));
}

int main() {
  // toggle it as output
  uint8_t redByte = 0x0f;
  uint8_t blueByte = 0x00;
  uint8_t greenByte = 0x00;

  DDR |= 1 << P;

  while (1) {
    // let's see how fast i can toggle this
    sendBit(0xff);
    sendBit(0x00);
  }
  return 0;
}
```

- HIGH: 2 cycles
- LOW: 4 cycles

no performance loss!

Now, we gotta abstract it away even further:

```c
#include <avr/io.h>
#include <stdint.h>

#define DDR DDRD
#define P PD6
#define PORT PORTD

const uint8_t PIN_MASK = 1 << P;

static inline void sendBit(uint8_t mask) {
  // assume that mask is correctly, either 0x00 or 0xff
  PORT = ((PORT & (~PIN_MASK)) | (PIN_MASK & mask));
}

static inline void sendByte(uint8_t byteToSend) {
  // i belive, we send MSB
  sendBit(-((byteToSend >> 7) & 1));
  sendBit(-((byteToSend >> 6) & 1));
  sendBit(-((byteToSend >> 5) & 1));
  sendBit(-((byteToSend >> 4) & 1));
  sendBit(-((byteToSend >> 3) & 1));
  sendBit(-((byteToSend >> 2) & 1));
  sendBit(-((byteToSend >> 1) & 1));
  sendBit(-((byteToSend >> 0) & 1));
}
int main() {
  // toggle it as output
  uint8_t redByte = 0x0f;
  uint8_t blueByte = 0x00;
  uint8_t greenByte = 0x00;

  DDR |= 1 << P;

  uint8_t byteToSend = 0b10101010;

  while (1) {
    sendByte(byteToSend);
  }
  return 0;
}
```

- HIGH: 793ns (13 cycles)
- LOW: 838ns (14 cycles)

this is really bad... we just added like 10 cycles. Let's use a different optimiser flag, let's use -03 instead.

```c
#include <avr/io.h>
#include <stdint.h>

#define DDR DDRD
#define P PD6
#define PORT PORTD

const uint8_t PIN_MASK = 1 << P;

static inline void sendBit(uint8_t mask) {
  // assume that mask is correctly, either 0x00 or 0xff
  PORT = ((PORT & (~PIN_MASK)) | (PIN_MASK & mask));
}

static inline void sendByte(uint8_t byteToSend) {
// i belive, we send MSB (please compiler... unroll loop for me...)
#pragma GCC unroll 8
  for (int i = 7; i >= 0; i--) {
    sendBit(-((byteToSend >> i) & 1));
  }
}
int main() {
  // toggle it as output
  uint8_t redByte = 0x0f;
  uint8_t blueByte = 0x00;
  uint8_t greenByte = 0x00;

  DDR |= 1 << P;

  uint8_t byteToSend = 0b10101010;
  while (1) {
    sendByte(byteToSend);
  }
  return 0;
}
```

- HIGH: 2 cycles
- LOW: 2 cycles (while sending the byte, not counting the while loop overhead)

ok... idk why but this now works even with the `-Os`flag... weird...

