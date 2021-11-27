obj-m := led.o
export ARCH=arm
export CROSS_COMPILE=arm-linux-gnueabi-

all : led.h led.c
	arm-linux-gnueabi-gcc -c led.c -o led.o
	arm-linux-gnueabi-ar rc libMyPeri.a led.o
