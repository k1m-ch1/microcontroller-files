# just defining variables
MCU = atmega328p
F_CPU = 16000000UL

CC = avr-gcc
OBJCOPY = avr-objcopy
AVRDUDE = avrdude

CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) -Os
FFLAGS = -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex:i

FLASH_READ_FLAGS = -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:r:dump.hex:i
FLASH_VERIFY_FLAGS = -c arduino -p m328p -P /dev/ttyUSB0 -b 115200 -U flash:v:main.hex:i

TARGET = main

all: $(TARGET).hex

# -O ihex means it's Intel HEX format
# ELF sections -> HEX records?
# -R .eeprom means remove the .eeprom section
$(TARGET).hex:$(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(TARGET).elf:$(TARGET).o
	$(CC) -mmcu=$(MCU) $< -o $@

$(TARGET).o:$(TARGET).c
	$(CC) -mmcu=$(MCU) $(CFLAGS) -c $< -o $@

flash:
	avrdude $(FFLAGS)

flash_read:
	avrdude $(FLASH_READ_FLAGS)

flash_verify:
	avrdude $(FLASH_VERIFY_FLAGS)

clean:
	rm -rf $(TARGET).hex $(TARGET).elf $(TARGET).o
