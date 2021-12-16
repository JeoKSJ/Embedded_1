CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all : libMyPeri.a main

main : main.c libMyPeri.a
	$(CC) main.c -o main -l MyPeri -L. -lpthread
libMyPeri.a : button.o buzzer.o fnd.o textlcd.o colorLed.o temperature.o
	$(AR) rc libMyPeri.a button.o buzzer.o fnd.o textlcd.o colorLed.o temperature.o

buzzer.o : buzzer.c buzzer.h
	$(CC) -c -o buzzer.o buzzer.c
colorLed.o: colorLed.c colorLed.h
	$(CC) -c -o colorLed.o colorLed.c
temperature.o : temperature.c temperature.h
	$(CC) temperature.c -o temperature.o -c
button.o : button.h button.c
	$(CC) button.c -o button.o -c
textlcd.o : textlcd.h textlcd.c
	$(CC) textlcd.c -o textlcd.o -c
fnd.o : fnd.c fnd.h
	$(CC) fnd.c -o fnd.o -c
clean :
	rm -rf *.o *.a
