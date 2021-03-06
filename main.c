#include <stdio.h>

#include "lcd.h"
#include "wiegand.h"

int main() {
  LCD_Init();
  wiegand_init();

  uint64_t result;
  uint8_t count;
  char output[20];

  LCD_Clear();
  while (1) {
    result = wiegand_read(&count); // blocks until read

    if (count == 26) {
      sprintf(output, "%03u %05u", (uint8_t)((result >> 17) & 0xff), (uint16_t)((result >> 1) & 0xffff));
    } else if (count == 35) {
      sprintf(output, "%04u %07lu", (uint16_t)((result >> 21) & 0xfff), (uint32_t)((result >> 1) & 0xfffff));
    }
    LCD_Clear();
    LCD_String(output);

    if (count > 32) {
      sprintf(output, "%ub:%x%08lx", count, (uint16_t)(result >> 32 & 0xffff), (uint32_t)(result & 0xffffffff));
    } else {
      sprintf(output, "%ub:%lx", count, (uint32_t)result);
    }
    LCD_Cursor(1, 0);
    LCD_String(output);
  }

  return 0;
}
