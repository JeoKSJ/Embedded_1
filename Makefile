all : final.elf
	gcc final.elf -c 1.o 2.o
1.o : 1.c myProject.h
	gcc 1.c -o 1.o
2.o : 2.c myProject.h
	gcc 2.c -o 2.o
