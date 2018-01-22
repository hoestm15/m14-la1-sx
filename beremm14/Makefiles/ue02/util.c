#include <avr/io.h>

void toggleLED() {
    PORTB ^= (1<<PB5);
}