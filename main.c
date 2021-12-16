#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h> 
#include <pthread.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>
#include <getopt.h>

#include <linux/spi/spidev.h>
#include <linux/input.h>
#include <linux/types.h>

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h> 
#include <sys/msg.h>

#include "button.h" 
#include "buzzer.h" 
#include "colorLed.h" 
#include "textlcd.h"
#include "fnd.h"
#include "temperature.h"

#define INPUT_DEVICE_LIST "/dev/input/event"
#define PROBE_FILE "/proc/bus/input/devices"

static int Fire_Emerge = 0; // 0 -> Green | 1-> Yellow | 2 -> Orange | 3 -> Red & Fire_Alarm On

int init() // Init Func
{
    pwmLedInit();
    buttonInit();
    buzzerInit(); 
    textlcdinit();
}
int light_green() // Green
{
    pwmSetPercent(0,0);
    pwmSetPercent(100,1);
    pwmSetPercent(0,2);
}
int light_yellow() // Yellow
{
    pwmSetPercent(0,0);
    pwmSetPercent(100,1);
    pwmSetPercent(100,2);
}
int light_orange() // Orange
{
    pwmSetPercent(0,0);
    pwmSetPercent(50,1);
    pwmSetPercent(100,2);
}
int light_red() // Red
{
    pwmSetPercent(0,0);
    pwmSetPercent(0,1);
    pwmSetPercent(100,2);
}

int lcdtime(){ // 현재시간 출력
    int number;
    struct tm *ptmcur;
    time_t tTime;
    if ( -1 == time(&tTime) )
	    return -1; 

    ptmcur = localtime(&tTime);

    number = ptmcur->tm_hour * 10000;
    number += ptmcur->tm_min *100;
    number += ptmcur->tm_sec;
    return (char)number;
}

void FNDLight_temperature() // FND에 1초마다 온도 측정값 & 현재 시간 출력 (이건 끊기지않게끔 조정)
{
    while(1)
    {
        fndtime();

        double temp = nowTemp();
        char buf[10];
        printf("current temperature is %lf \n",temp);
        sprintf(buf, "%lf", temp);
        textlcdwrite("Current Temperature",buf,0); // 현재 시간 1초마다 TXTLCD에 띄움

        // 온도 관련 현재 상태를 ColorLED에 표시
        if (temp < 30) // 초록(편안)
        {
            light_green();
            if(Fire_Emerge != 0) Fire_Emerge = 0;
        }
        else if(temp >= 30 && temp < 50) // 노랑(더움) & 경보 1단계
        {
            light_yellow();
            if(Fire_Emerge != 1) Fire_Emerge = 1; // 위험 1단계로 설정
        }
        else if(temp >= 50 && temp  < 80) // 주황(뜨거움) & 경보 2단계
        {
            light_orange();
            if(Fire_Emerge != 2) Fire_Emerge = 2; // 위험 2단계로 설정
        }
        else if(temp >= 80) // 빨강(화재 가능성 & 경보)
        {
            light_red();
            if(Fire_Emerge != 3) Fire_Emerge = 3; // 화재가 났음으로 설정
        }
        sleep(1); // 이건 잘 모르겠음
    }
}

int fire_alarm()
{
    while(1)
    {
        if(Fire_Emerge != 0) {buzzerSiren();}
    }
}
int button1(void) // 버튼 1 누를 시 : 사용법 화면
{

}
int button2(void) // 버튼 2 누를 시 : 작동 예시 화면(모든것 다 작동)
{

}
int button3(void) // 버튼 3 누를 시 : 실제 상황(현재 상황 표시)
{
    switch (Fire_Emerge)
    {
    case 0: // 정상
        
        break;
    case 1: // 주의

        break;
    case 2: // 위험

        break;
    }
}
int main(int argc, char **argv)
{
    init(); // 전체 초기화

    FNDLight_temperature();
    

}
