CC = arm-linux-gnueabi-gcc
AR = arm-linux-gnueabi-ar

all : libMyPeri.a accelMagGyroTest
		
libMyPeri.a : accelMagGyro.o
	$(AR) rc libMyPeri.a accelMagGyro.o

accelMagGyro.o : accelMagGyro.c accelMagGyro.h
	$(CC) accelMagGyro.c -o accelMagGyro.o -c

accelMagGyroTest : accelMagGyroTest.c accelMagGyro.h libMyPeri.a
	$(CC) accelMagGyroTest.c -o accelMagGyroTest -l MyPeri -L.	
	
clean: 
	rm -rf *.a *.o accelMagGyroTest
