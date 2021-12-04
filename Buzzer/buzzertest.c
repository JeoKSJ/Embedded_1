#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#define MAX_SCALE_STEP 8
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/”
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"

char gBuzzerBaseSysDir[128]; ///sys/bus/platform/devices/peribuzzer.XX 가 결정됨
const int musicScale[MAX_SCALE_STEP] = // 구조체 musicScale 선언
{
    262, /*do*/ 294,330,349,392,440,494, /* si */ 523
};

int main(int argc , char **argv)
{
    int freIndex;

    if (argc < 2) // 찾기 실패시
    {
        printf("Error!\n");
        printf("Usage:\n");
        printf("buzzertest <buzzerNo> \n");
        printf("buzzerNo: \n");
        printf("do(1),re(2),mi(3),fa(4),sol(5),ra(6),si(7),do(8) \n");
        printf("off(0)\n");
        return 1;
    }

    freIndex = atoi(argv[1]);
    printf("freIndex :%d \n",freIndex);

    if ( freIndex > MAX_SCALE_STEP )
    {
        printf(" <buzzerNo> over range \n");
        return 1;
    }
    if (freIndex == 0)// disable
    {
        buzzerStopSong();
        return 0;
    }
    else
    {
        buzzerPlaySong(musicScale[freIndex]);
        buzzerExit();
    }
    return 0;
}
