CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all: libMyPeri.a fndtest

libMyPeri.a : fnd.o
	$(AR) rc libMyPeri.a fnd.o

fnd.o : fnd.h fnd.c
	$(CC) fnd.c -o fnd.o -c

fndtest : fndtest.c fnd.h libMyPeri.a
	$(CC) fndtest.c -o fndtest -l MyPeri -L.

clean:
	rm *.o -rf
	rm *.a -rf
	rm fndtest -rf
