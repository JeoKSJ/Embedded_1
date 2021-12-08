#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "textlcd.h"



#define TEXTLCD_DRIVER_NAME		"/dev/peritextlcd"

void doHelp(void)
{
	printf("usage: textlcdtest <linenum> <'string'>\n");
	printf("       linenum => 1 ~ 2\n");	
	printf("  ex) textlcdtest 2 'test hello'\n");
	
}


int main(int argc , char **argv)
{
	unsigned int linenum = 0;

	
	


	textlcdinit();
	
	if (argc < 3 )
	{
		perror(" Args number is less than 2\n");
		doHelp();
		return 1;
	}
	
	linenum = strtol(argv[1],NULL,10);
	printf("linenum(test.c) :%d\n", linenum);

	printf("string:%s\n",argv[2]);
	printf("string:%s\n",argv[3]);
	if(argv[3]==NULL)
	{argv[3]="a";}
	textlcdwrite(argv[2],argv[3],linenum);
	
	textlcdexit();
	
	return 0;
}
