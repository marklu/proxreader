#include <avr/io.h>
#include <util/delay.h>

#include "lcd.h"

void LCD_Send(char rs, char data)  {
  LCD_Data_Port = data;

  if (rs) LCD_Command_Port |= (1<<RS);
  else LCD_Command_Port &= ~(1<<RS);

  LCD_Command_Port &= ~(1<<RW); /* RW=0 write operation */
  LCD_Command_Port |= (1<<EN); /* Enable Pulse */
  _delay_us(1);
  LCD_Command_Port &= ~(1<<EN);
  _delay_ms(2); /* Data write delay */
}

void LCD_Clear() {
  LCD_Command(0x01); /* clear display */
  LCD_Command(0x80); /* cursor at home position */
}

void LCD_Init() {
  LCD_Command_Dir = 0xFF; /* Make LCD command port direction as o/p */
  LCD_Data_Dir = 0xFF; /* Make LCD data port direction as o/p */
  _delay_ms(20); /* LCD Power ON delay always >15ms */
  
  LCD_Command(0x38); /* Initialization of 16X2 LCD in 8bit mode */
  LCD_Command(0x0C); /* Display ON Cursor OFF */
  LCD_Command(0x06); /* Auto Increment cursor */
  LCD_Clear();
}

void LCD_String(char *str) {
  int i = 0;
  while (str[i]) LCD_Data(str[i++]);
}

