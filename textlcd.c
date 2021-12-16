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

stTextLCD  stlcd; 
stTextLCD  stlcd2; 
int fd;



void textlcdinit(void)
{
	fd = open(TEXTLCD_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		
	}
	printf("hihi\r\n");
    memset(&stlcd,0,sizeof(stTextLCD));
	//memset(&stlcd2,0,sizeof(stTextLCD));
}

int textlcdwrite(const char *str1, const char *str2, int lineflag)
{
	printf("lineflag: %d\r\n", lineflag);
	int len = strlen(str1);
	int len2 = strlen(str2);

	if (lineflag == 0) //BOTH LINE
	{
		stlcd.cmdData = CMD_DATA_WRITE_BOTH_LINE;
		//stlcd2.cmdData = CMD_DATA_WRITE_BOTH_LINE;
		if ( len > COLUMN_NUM)
		{
			memcpy(stlcd.TextData[stlcd.cmdData ],str1,COLUMN_NUM);
			memcpy(stlcd.TextData[stlcd.cmdData + 1],str2,COLUMN_NUM);
		}
		else
		{   
			memcpy(stlcd.TextData[stlcd.cmdData ],str1,len);
			memcpy(stlcd.TextData[stlcd.cmdData + 1],str2,len2);
		}
		//if ( len2 > COLUMN_NUM)
		//	{
		//		memcpy(stlcd2.TextData[stlcd2.cmdData - 1],str2,COLUMN_NUM);
		//	}
		//	else
		//	{
		//		memcpy(stlcd2.TextData[stlcd2.cmdData - 1],str2,len);
		//	}
	}
	else if ( lineflag == 1) // firsst line
	{
		stlcd.cmdData = CMD_DATA_WRITE_LINE_1;
        if ( len > COLUMN_NUM)
		{
			memcpy(stlcd.TextData[stlcd.cmdData - 1],str1,COLUMN_NUM);
		}
		else
		{
			memcpy(stlcd.TextData[stlcd.cmdData - 1],str1,len);
	 	}
	}
	else if ( lineflag == 2) // second line
	{
		stlcd.cmdData = CMD_DATA_WRITE_LINE_2;
        if ( len > COLUMN_NUM)
	 	{
			memcpy(stlcd.TextData[stlcd.cmdData - 1],str1,COLUMN_NUM);
	 	}
		else
	 	{
			memcpy(stlcd.TextData[stlcd.cmdData - 1],str1,len);
	 	}
	}
	else 
	{
		printf("lineflag : %d  wrong .  range (0 ~ 2)\n", lineflag);
		return 1; 
	}
	
	stlcd.cmd = CMD_WRITE_STRING;

	write(fd,&stlcd,sizeof(stTextLCD));
	//write(fd,&stlcd2,sizeof(stTextLCD));

	return 7;
}

void textlcdexit()
{
	close(fd);
}



