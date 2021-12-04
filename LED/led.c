#include "led.h" // 헤더파일 참조
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static int ledStatus = 0;
static int fd = 0; 
int ledLibInit(void) // LED 초기화
{   
	printf("LED LIBRARY INITIALIZE...\r\n");
	fd = open(LED_DRV_NODE, O_RDWR);
    printf("FD: %d\r\n", fd); // 디바이스 드라이버 개방
    if (fd<0)
	{
		printf("Device open error!\n\r");
		exit(1);
	}
	ledStatus =0;
	ledLibRaw(ledStatus);
	return 1;
	//ledValue = 0; // LED 값 0으로 초기화
}
int ledLibOnOff(int ledNumber, int onOff) // LED 켜기 / 끄기
{
	int i = 1; 
	i = i << ledNumber; //00010000 해당하는 전구bit만 1로바뀜
	ledStatus = (ledStatus & (~i));
	if(onOff != 0) ledStatus |= i; // 요기까지로 지정 LED 센서만 사용하게끔 지정 가능(1 << 로 LED의 사용 할 것을 지정할 수 있음.
	ledLibRaw(ledStatus); 
    return 1;
}
int ledLibStatus(void)
{
 	return ledStatus;
}
int ledLibBlink(int ledNumber, int nth, int msec)
{
	ledLibMorseBlink(ledNumber, nth, msec, msec);
} //1~8까지의 LED를 하다 골라서 N번 깜박임.주기는 MSEC

int ledLibMorseBlink(int ledNumber, int nth, int msecOn, int msecOff)
{
	int i=0;
	for(i=0;i<nth;i++)
	{
		ledLibOnOff(ledNumber,1); //on
		usleep(1000*msecOn);
		ledLibOnOff(ledNumber,0); //OFF
		usleep(1000*msecOff);
	}
}

int ledLibExit(void) // 종료 함수
{
	
	ledLibRaw(0); // LED를 전체 끔(LedNum = 0, onOff = 0)
	close(fd); // file description 닫음
}


int ledLibRaw(char ledwannabe){
	if(fd >0)
	{ 
		write(fd, &ledwannabe, 1);
		//do something
	}
	else
	{
	printf("Wrong! you must open device Node!\r\n");
	exit(2);
	}
	ledStatus = ledwannabe;
	return 1;
}
//이 함수를 호출하면 ledwannabe에 맞게 8개의 led를 전부 제어한다. 예를 들어 ledLibRaw(0x80); 1개만 켜진다.

