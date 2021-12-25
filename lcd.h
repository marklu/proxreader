#include <avr/io.h>
#include <util/delay.h>

#define LCD_Data_Dir DDRB
#define LCD_Data_Port PORTB
#define LCD_Command_Dir DDRC
#define LCD_Command_Port PORTC
#define RS PC0
#define RW PC1
#define EN PC2

void LCD_Send(char, char);
#define LCD_Command(data) LCD_Send(0, data);
#define LCD_Data(data) LCD_Send(1, data);

void LCD_Clear();
void LCD_Init();
void LCD_String(char*);
