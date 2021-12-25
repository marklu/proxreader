#include <avr/io.h>
#include <util/delay.h>

#define LCD_Data_Dir DDRA
#define LCD_Data_Port PORTA
#define LCD_Command_Dir DDRE
#define LCD_Command_Port PORTE
#define RS PE0
#define RW PE1
#define EN PE2

void LCD_Send(char, char);
#define LCD_Command(data) LCD_Send(0, data);
#define LCD_Data(data) LCD_Send(1, data);

void LCD_Clear();
void LCD_Init();
void LCD_String(char*);
