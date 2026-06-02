CC = avr-gcc
TARGET = main
OBJCOPY = avr-objcopy
CFLAGS = -mmcu=atmega328p -DF_CPU=16000000UL -O3

all: $(TARGET).hex

$(TARGET).hex:$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(TARGET).elf:$(TARGET).c
	$(CC) $(CFLAGS) $< -o $@

flash:
	avrdude -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:w:$(TARGET).hex:i

clean:
	rm $(TARGET).hex $(TARGET).elf
