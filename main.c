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

static int Fire_Emerge = 0; // -1 -> Blue | 0 -> Green | 1-> Yellow | 2 -> Orange | 3 -> Red & Fire_Alarm On

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
    pwmSetPercent(255,1);
    pwmSetPercent(0,2);
}
int light_blue() // Blue
{
    pwmSetPercent(255,0);
    pwmSetPercent(178,1);
    pwmSetPercent(102,2);
}
int light_yellow() // Yellow
{
    pwmSetPercent(0,0);
    pwmSetPercent(255,1);
    pwmSetPercent(255,2);
}
int light_orange() // Orange
{
    pwmSetPercent(0,0);
    pwmSetPercent(128,1);
    pwmSetPercent(255,2);
}
int light_red() // Red
{
    pwmSetPercent(0,0);
    pwmSetPercent(0,1);
    pwmSetPercent(255,2);
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
}
void FNDLight_temperature() // FND에 1초마다 온도 측정값 & 현재 시간 출력 (이건 끊기지않게끔 조정)
{
    char *buffer; 
    int file;

    file = spi_init("/dev/spidev1.0"); // dev
    buffer = (char *)spi_read_lm74(file);
    close(file);

    int value = 0; // 13비트 Big Endian Signed Int를 16비트 Little Endian Signed Int로 바꾼다

    value = (buffer[1] >> 3); // Last 3bit: Trashes 날려버리는 함수: 남은 5비트만 value에 더해짐
    value += (buffer[0]) << 5; // 위에서 5비트 더한거에 상위 8비트 (= 13비트) 를 원하는 값으로 채움

    if ( buffer[0] & 0x80 ) // 만약 buffer[0]의 최상위 8번째 비트가 1이라면 사실은 음수 = 영하 기온이 디텍팅 된 것
    {   // 그럼 value의 32번 비트에서부터 14번 비트까지 1로 채워 줘야 함 (2의 보수, 음수 참고)
        int i = 0;
        for (i = 31;i > 12; i--)
            value |= (1 << i); // 1로 비트를 채움
    }

    double temp = (double)value * 0.0625;
        // 1비트가 0.0625도

    while(1)
    {
        fndDisp('s', temp); // FND에 지속적으로 온도 측정값을 띄움. 주기는 1초
        textlcdwrite("Current Time.",lcdtime(),0); // 현재 시간 1초마다 TXTLCD에 띄움

        // 온도 관련 현재 상태를 ColorLED에 표시
        if (temp < 30 && temp >= 5) // 초록(편안)
        {
            light_green();
        }
        else if(temp < 5) // 파랑(추움)
        {
            light_blue();
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
        buzzerSiren();
    }

    if()
    {
        buzzerStopSong();
    }
}
int button1() // 버튼 1 누를 시 : 사용법 화면
{

}
int button2() // 버튼 2 누를 시 : 작동 예시 화면(모든것 다 작동)
{

}
int button3() // 버튼 3 누를 시 : 실제 상황(현재 상황 표시)
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

    while(1){
        if(Fire_Emerge < 3){
            
        }
    }


}