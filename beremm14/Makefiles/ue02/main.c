#define F_CPU 16000000L
#include <avr/io.h>
#include <util/delay.h>
#include "util.h"

int main () {
  DDRB = (1<<PB5);

  while (1) {
    toggleLED();
    _delay_ms(500);
    }

  return 0;
}