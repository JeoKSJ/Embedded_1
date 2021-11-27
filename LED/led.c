#include "led.h" // 헤더파일 참조
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int ledValue = 0;
static int fd = 0; 
int ledOnOff(int ledNum, int onOff) // LED 켜기 / 끄기
{
	int i = 1; 
	i = i << ledNum; 
	ledValue = ledValue & (~i);
	if(onOff != 0) ledValue |= i; // 요기까지로 지정 LED 센서만 사용하게끔 지정 가능(1 << 로 LED의 사용 할 것을 지정할 수 있음.
	write(fd, &ledValue, 4); // write로 현재 읽은 값을 저장해서 LED 센서를 활성화함.
}
int ledStatus(void);
int ledLibInit(void) // LED 초기화
{
	fd = open("/dev/periled", O_WRONLY); // 디바이스 드라이버 개방
	ledValue = 0; // LED 값 0으로 초기화
}

int ledLibExit(void) // 종료 함수
{
	ledValue = 0; // LED 값을 0으로 초기화
	ledOnOff(0, 0); // LED를 전체 끔(LedNum = 0, onOff = 0)
	close(fd); // file description 닫음
}
