#include <avr/io.h>
#include <util/delay.h>

#define DELAY_TIME 2000

int main() {
  DDRB |= (1 << PB5);
  while (1) {
    PORTB |= (1 << PB5);
    _delay_ms(DELAY_TIME);
    PORTB &= ~(1 << PB5);
    _delay_ms(DELAY_TIME);
  }
}
