CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all : libMyPeri.a buttontest

libMyPeri.a : button.o
	$(AR) rc libMyPeri.a button.o

button.o : button.h button.c
	$(CC) button.c -o button.o -c

buttontest : buttontest.c button.h libMyPeri.a
	$(CC) buttontest.c -o buttontest -l MyPeri -L. -lpthread

clean :
	rm *.0 -rf
	rm *.a -rf
	rm buttontest -rf
