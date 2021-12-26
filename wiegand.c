#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>

volatile uint64_t wiegand_result;
volatile int wiegand_count;
volatile int wiegand_timeout;

ISR (INT0_vect) {
  wiegand_timeout = 0;
  wiegand_result <<= 1;
  wiegand_count++;
}

ISR (INT1_vect) {
  wiegand_timeout = 0;
  wiegand_result <<= 1;
  wiegand_result |= 1;
  wiegand_count++;
}

ISR (TIMER0_OVF_vect) {
  if (wiegand_count) wiegand_timeout++;
}

void wiegand_init() {
  DDRD |= 0xe0; // configure INT0, INT1 as input
  GICR = 0xc0; // enable INT0, INT1 as interrupts
  MCUCR = 0x0a; // INT0, INT1 on falling edge
}

uint64_t wiegand_read(int *count) {
  wiegand_result = 0;
  wiegand_count = 0;
  wiegand_timeout = 0;

  TCCR0 |= 0x05; // enable timer0 at f_clk/1024
  TIMSK |= (1 << TOIE0); // enable timer0 interrupts

  while (1) {
    sleep_enable(); // set SE bit
    sei(); // enable global interrupts
    sleep_cpu(); // sleep until interrupt
    sleep_disable(); // clear SE bit
    if (wiegand_timeout > 8) break;
  }

  TCCR0 = 0; // disable timer0
  TIMSK &= ~(1 << TOIE0); // disable timer0 interrupts
  *count = wiegand_count;
  return wiegand_result;
}
