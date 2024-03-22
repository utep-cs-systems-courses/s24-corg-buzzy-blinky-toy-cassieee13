#makefile configuration
COMMON_OBJECTS = main.o
CPU = msp430g2553
CFLAGS = -mmcu=${CPU}-I../h
LDFLAGS = -L/opt/ti/msp430_gcc/include

#switch the compiler (for the internal make rules)
CC = msp430-elf-gcc
AS = msp430-elf-as

all: toy.elf

#additional rules for files
toy.elf: ${COMMON_OBJECTS}
	${CC}${CFLAGS}${LDFLAGS} -o$@%^../lib/libtimer.a

load: toy.elf
	msp430loader.sh toy.elf

clean:
	rm -f*.o*.elf

main.o: led.h

wdInterruptHandler.o: led.h
