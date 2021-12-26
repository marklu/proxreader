#include <avr/interrupt.h>
#include <avr/sleep.h>

volatile uint32_t wiegand_result = 0;
volatile int wiegand_count = 0;

ISR (INT0_vect) {
  wiegand_result <<= 1;
  wiegand_count++;
}

ISR (INT1_vect) {
  wiegand_result <<= 1;
  wiegand_result |= 1;
  wiegand_count++;
}

void wiegand_init() {
  DDRD |= 0xe0; // configure INT0, INT1 as input
  GICR = 0xc0; // enable INT0, INT1 as interrupts
  MCUCR = 0x0a; // INT0, INT1 on falling edge
}

uint32_t wiegand_read(int bits) {
  wiegand_result = 0;
  wiegand_count = 0;

  while (1) {
    sleep_enable(); // set SE bit
    sei(); // enable global interrupts
    sleep_cpu(); // sleep until interrupt
    sleep_disable(); // clear SE bit
    if (wiegand_count >= bits) return wiegand_result;
  }
}
