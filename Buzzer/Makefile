CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all : libMyPeri.a buzzertest

buzzer.o : buzzer.c buzzer.h
	$(CC) -c -o buzzer.o buzzer.c

libMyPeri.a : buzzer.o
	$(AR) rc libMyPeri.a buzzer.o

buzzertest : buzzertest.c buzzer.h libMyPeri.a
	$(CC) buzzertest.c -o buzzertest -l MyPeri -L. -lpthread
clean :
	rm -rf *.o *.a ledtest
