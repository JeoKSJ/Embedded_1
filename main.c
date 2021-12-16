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


int init() // 초기화 함수들
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
int light_blue()
{
    pwmSetPercent(255,0);
    pwmSetPercent(178,1);
    pwmSetPercent(102,2);
}
int light_yellow()
{
    pwmSetPercent(0,0);
    pwmSetPercent(255,1);
    pwmSetPercent(255,2);
}
int light_orange()
{
    pwmSetPercent(0,0);
    pwmSetPercent(128,1);
    pwmSetPercent(255,2);
}
int light_red()
{
    pwmSetPercent(0,0);
    pwmSetPercent(0,1);
    pwmSetPercent(255,2);
}
void FNDLight_temperature() // FND에 1초마다 온도 측정값 출력 (이건 끊기지않게끔 조정)
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
    
    // 여기까지 온도 읽어내기 후 지속적으로 출력
    while(1)    
    {
        fndDisp('s', temp); // FND에 지속적으로 온도 측정값을 띄움. 주기는 1초
        // 온도별 색상지정(BGR)
        if (temp < 40 && temp >= 5) // 초록(편안)
        {
            light_green();
        }
        else if(temp >= 40 && temp <= 60) // 노랑(더움 & 경보 1단계)
        {
            light_yellow();
        }
        else if(temp < 5) // 파랑(추움)
        {
            light_blue();
        }
        else if(temp > 60 && temp  < 100) // 주황(뜨거움 & 경보 2단계)
        {
            light_orange();
        }
        else if(temp > 100) // 빨강(화재 가능성 & 경보 3단계)
        {
            // 온도가 너무 높으면 화면에 화재 경보가 있습니다! 띄우기
            light_red();

        }
        sleep(1);
    }
}

int button1() // 버튼 1 누를 시
{

}
int button2() // 버튼 2 누를 시
{

}
int button3() // 버튼 3 누를 시
{
    
}
int main(int argc, char **argv)
{
    init();

    BUTTON_MSG_T RxDataButton;
    int msgID = msgget(MESSAGE_ID, IPC_CREAT|0666);

    textlcdwrite(" "," ",0); // 두줄 사용해서 말귀 만들기
    while(1){
        if(msgrcv(msgID, &RxDataButton, sizeof(RxDataButton)-sizeof(RxDataButton.messageNum),0,0) != -1){
            switch (RxDataButton.keyInput)
            {
                case 0: // Home 버튼
                    button1;
                    break;
                case 1: // " " 버튼
                    button2;
                    break;
                case 2: // 실험메뉴 버튼 등등..
                    button3;
                    break;
            }
        }
    }


}