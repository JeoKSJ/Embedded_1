CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all : libMyPeri.a temperatureTest
		
libMyPeri.a : temperature.o
	$(AR) rc libMyPeri.a temperature.o

temperature.o : temperature.c temperature.h
	$(CC) temperature.c -o temperature.o -c

temperatureTest : temperatureTest.c temperature.h libMyPeri.a
	$(CC) temperatureTest.c -o temperatureTest -l MyPeri -L.	
	
clean: 
	rm -rf *.a *.o temperatureTest
