PRJ = main
MCU = atmega8515
CLK = 8000000
SRC = main.c lcd.c wiegand.c

INCLUDE := $(foreach dir, $(EXT), -I$(dir))
CFLAGS = -Wall -Os -DF_CPU=$(CLK) -mmcu=$(MCU) $(INCLUDE)

OBJCOPY = avr-objcopy
OBJDUMP = avr-objdump
SIZE = avr-size --format=avr --mcu=$(MCU)
CC = avr-gcc

CFILES = $(filter %.c, $(SRC))
OBJ = $(CFILES:.c=.o) $(EXTC:.c=.o)

all: $(PRJ).hex

clean:
	rm -f *.hex *.elf *.o
	$(foreach dir, $(EXT), rm -f $(dir)/*.o;)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(PRJ).elf: $(OBJ)
	$(CC) $(CFLAGS) -o $(PRJ).elf $(OBJ)

$(PRJ).hex: $(PRJ).elf
	rm -f $(PRJ).hex
	$(OBJCOPY) -j .text -j .data -O ihex $(PRJ).elf $(PRJ).hex
	$(SIZE) $(PRJ).elf
