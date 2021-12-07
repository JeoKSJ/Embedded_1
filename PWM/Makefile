CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all: libMyPeri.a colorLedtest

colorLedtest: libMyPeri.a colorLedtest.c colorLed.h
	$(CC) colorLedtest.c -o colorLedtest -l MyPeri -L.

colorLed.o: colorLed.c colorLed.h
	$(CC) -c -o colorLed.o colorLed.c

libMyPeri.a : colorLed.o
	$(AR) rc libMyPeri.a colorLed.o

clean:
	rm *.o *.a colorLedtest -rf
