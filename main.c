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
static int hi = 0;
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
int light_white() // 
{
    pwmSetPercent(100,0);
    pwmSetPercent(100,1);
    pwmSetPercent(100,2);
}
/*


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
*/
int main(void)//void FNDLight_temperature() // FND에 1초마다 온도 측정값 & 현재 시간 출력 (이건 끊기지않게끔 조정)
{
    init();
    BUTTON_MSG_T RxDataButton;
    int msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);

    while(1){
        double temp = nowTemp();
        int temp2 = (int)temp;
        fndDisp(temp2, 0);
        printf("current temperature is %lf \n",temp);
        textlcdwrite("Fire_alarm_call","Test:30~32 (C)",0); // 현재 시간 1초마다 TXTLCD에 띄움
        // 온도 관련 현재 상태를 ColorLED에 표시
        if (temp < 30.0) // 초록(편안)
        {
            light_green();
            if(Fire_Emerge != 0) Fire_Emerge = 0;
        }
        else if(temp >= 30 && temp < 31) // 노랑(더움) & 경보 1단계
        {
            light_yellow();
            if(Fire_Emerge != 1) Fire_Emerge = 1; // 위험 1단계로 설정
        }
        else if(temp >= 31 && temp  < 32) // 주황(뜨거움) & 경보 2단계
        {
            light_orange();
            if(Fire_Emerge != 2) Fire_Emerge = 2; // 위험 2단계로 설정
        }
        else if(temp >= 32) // 빨강(화재 가능성 & 경보)
        {
            light_red();
            if(Fire_Emerge != 3) Fire_Emerge = 3; // 화재가 났음으로 설정
        }
        if(Fire_Emerge == 3)
        {
            buzzerPlaySong(7);
        }
        else
        {
            buzzerStopSong();
        }
        sleep(1);

    }
}
/*
int button1(void) // 버튼 1 누를 시 : 사용법 화면
{
    textlcdwrite("button2:ex_alarm","button3:temper",0);
}
    int button2(void) // 버튼 2 누를 시 : 작동 예시 화면(모든것 다 작동)
{
    Fire_Emerge = 3; // 누르는 동안은 지속
}
int button3(void) // 버튼 3 누를 시 : 현재 상황 표시
{
    switch (Fire_Emerge)
    {
    case 0: // 정상
        textlcdwrite("Current Temper","GOOD(~30)",0);
        break;
    case 1: // 주의
        textlcdwrite("Current Temper","Caution(30~50)",0);
        break;
    case 2: // 위험
        textlcdwrite("Current Temper","Danger(50~80)",0);
        break;
    default: break;
    }
}
/*int main(int argc, char **argv)
{
    init(); // 전체 초기화
    FNDLight_temperature();
    BUTTON_MSG_T RxDataButton;
    int msgID = msgget(MESSAGE_ID, IPC_CREAT | 0666);
    while(1)
    {   
        hi = msgrcv(msgID, &RxDataButton, sizeof(RxDataButton)-sizeof(RxDataButton.messageNum),0,0);
        if(hi != -1)
        {
            switch (RxDataButton.keyInput)
            {
            case 0 : // Home 키
                textlcdwrite("button2:ex_alarm","button3:temper",0);
                sleep(3);
                
                break;
            case 1 : // Back 키
                button2();
                sleep(3);
                break;
            case 2 : // Search 키
                button3();
                sleep(3);
                break;
            default:break;
            }
        }
        sleep(1);
    }
    buttonExit();
}
*/
