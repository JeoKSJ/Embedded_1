final.elf : 1.o 2.o main.c
	gcc 1.o 2.o main.c -o final.elf
1.o : 1.c myProject.h
	gcc -c 1.c
2.o : 2.c myProject.h
	gcc -c 2.c
