#include <stdio.h>

#include "lcd.h"
#include "wiegand.h"

int main() {
  LCD_Init();
  wiegand_init();

  uint32_t result;
  uint8_t facility;
  uint16_t card;
  char output[16];

  LCD_Clear();
  while (1) {
    result = wiegand_read(26); // blocks until read

    facility = (result >> 17) & 0xff;
    card = (result >> 1) & 0xffff;

    sprintf(output, "%u %u", facility, card);
    LCD_Clear();
    LCD_String(output);
  }

  return 0;
}
