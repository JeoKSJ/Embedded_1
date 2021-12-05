#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include "buzzer.h"
#define MAX_SCALE_STEP	8										
#define BUZZER_BASE_SYS_PATH "/sys/bus/platform/devices/"		
#define BUZZER_FILENAME "peribuzzer"
#define BUZZER_ENABLE_NAME "enable"
#define BUZZER_FREQUENCY_NAME "frequency"

// buzzertest에 쓰는 scale 은 총 8개(262,294,330,349,392,440,494,523)
static char gBuzzerBaseSysDir[128];
int fd;
int findBuzzerSysPath(){ //버저 경로 찾는 것 = 버저의 초기화구문(buzzerInit)
    DIR * dir_info = opendir(BUZZER_BASE_SYS_PATH);
    int ifNotFound = 1;
    if (dir_info != NULL)
    {
        while (1)
        {
            struct dirent *dir_entry;
            dir_entry = readdir (dir_info);
            if (dir_entry == NULL) break;
            if (strncasecmp(BUZZER_FILENAME, dir_entry->d_name, strlen(BUZZER_FILENAME)) == 0){
                ifNotFound = 0;
                sprintf(gBuzzerBaseSysDir,"%s%s/",BUZZER_BASE_SYS_PATH,dir_entry->d_name);
            }
        }
    }
    printf("find %s\n",gBuzzerBaseSysDir);
    return ifNotFound;
}
void buzzerEnable(int bEnable) // 부저 활성화
{
    char path[200];
    sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_ENABLE_NAME);
    int fd = open(path, O_WRONLY); //읽기 전용
    if (bEnable) write(fd, &"1", 1); // 무언가가 적혀있을 시 실행
    else write(fd, &"0", 1);
    close(fd);
}

void setFrequency(int frequency) // 부저 Frequency(주파수) 설정
{
    char path[200];
    sprintf(path,"%s%s",gBuzzerBaseSysDir,BUZZER_FREQUENCY_NAME);
    int fd = open(path, O_WRONLY); // 읽기 전용
    dprintf(fd, "%d", frequency); // print descript에 바로 출력
    close(fd);
}
// 편하게 쓰기 위해서 앞 test구문에 있는 것을 가져왔습니다.(구문 내용 줄이기)


int buzzerInit(void) // 초기화
{
    if(findBuzzerSysPath() == 1) // 만약 버저의 경로를 못찾을 시
    {
        perror("Path Error!\r\n");
        return -1;
    }   
}
/* 사실 이것을 안해도 위에서 findBuzzerSysPath에서 ifNotFound를 바로 리턴시켜서 그 구문을 종료해도 된다.

*/
int buzzerPlaySong(int scale)
{
    int freq; // frequency 선언
    switch(freq)
    {
        case 0: // 262(도)
            freq = 262;
            break;
        case 1: // 294(레)
            freq = 294;
            break;
        case 2: // 330(미)
            freq = 330;
            break;
        case 3: // 349(파)
            freq = 349;
            break;
        case 4: // 392(솔)
            freq = 392;
            break;
        case 5: // 440(라)
            freq = 440;
            break;
        case 6: // 494(시)
            freq = 494;
            break;
        case 7: // 523(높은 도)
            freq = 523;
            break;
        default: // 이미 앞에서 처리되서 여긴 올 일이 없다.
            break;
    }
    buzzerEnable(1); // 부저 상태 활성화
    setFrequency(freq); // 주파수를 freq로 설정
}
int buzzerStopSong(void)
{
    buzzerEnable(0); // 부저 상태 비활성화
}
int buzzerExit(void)
{
    close(fd); // 위에서 findBuzzerSysPath로 찾은 경로에서 read로 열고 바로 닫음.
}
