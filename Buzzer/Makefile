CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all : libMyPeri.a buzzertest
	$(AR)rc libMyPeri.a buzzer.o
buzzer.o : buzzer.c buzzer.h
	$(CC) -c -o buzzer.o buzzer.c
buzzertest : buzzertest.c buzzer.h libMyPeri.a
	$(CC) buzzertest.c -o buzzer -l MyPeri -L
clean :
	rm -rf *.o *.a ledtest
