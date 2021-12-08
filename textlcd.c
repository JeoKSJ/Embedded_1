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
int fd;



void textlcdinit(void)
{

fd = open(TEXTLCD_DRIVER_NAME,O_RDWR);
	if ( fd < 0 )
	{
		perror("driver (//dev//peritextlcd) open error.\n");
		
	}
	




}

int textlcdwrite(const char *str1, const char *str2, int lineflag)
{


int len = strlen(str1);
int len2 = strlen(str2);
memset(&stlcd,0,sizeof(stTextLCD));
if (lineflag ==0) //BOTH LINE
{
stlcd.cmdData = CMD_DATA_WRITE_BOTH_LINE;
if ( len > COLUMN_NUM)
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],str1,COLUMN_NUM);
	}
	else
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],str1,len);
	}
if ( len2 > COLUMN_NUM)
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],str2,COLUMN_NUM);
	}
	else
	{
		memcpy(stlcd.TextData[stlcd.cmdData - 1],str2,len);
	}


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

return 7;
}

void textlcdexit()
{


close(fd);

}



