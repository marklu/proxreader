#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdlib.h>

#include "lcd.h"

int main() {
  LCD_Init();
  LCD_String("Hello World");
  _delay_ms(2000);

  int i = 0;
  char* outputStr = malloc(16);
  while(1) {
    itoa(i, outputStr, 10);
    LCD_Clear();
    LCD_String(outputStr);
    i++;
    _delay_ms(1000);
  }

  return 0;
}
