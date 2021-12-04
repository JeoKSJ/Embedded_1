#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>


// first read input device
#define INPUT_DEVICE_LIST "/dev/input/event"
//실제 디바이스 드라이버 노드파일: 뒤에 숫자가 붙음., ex)/dev/input/event5
#define PROBE_FILE "/proc/bus/input/devices"
//PPT에 제시된 "이 파일을 까보면 event? 의 숫자를 알수 있다"는 바로 그 파일
#include "button.h"



int main(int argc, char *argv[])
{
BUTTON_MSG_T RxDataButton;
int msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);

buttonInit();

while(1)
{
int bye;
bye = msgrcv(msgID, &RxDataButton, sizeof(RxDataButton)-sizeof(RxDataButton.messageNum),0,0);


if(bye != -1){
switch(RxDataButton.keyInput)
{

case 0: printf("SELECTED: Volume up key"); break;
case 1: printf("SELECTED: Home key"); break;
case 2: printf("SELECTED: Search key):"); break;
case 3: printf("SELECTED: Back key):"); break;
case 4: printf("SELECTED: Menu key):"); break;
case 5: printf("SELECTED: Volume down key):"); break;
}
}



}









buttonExit();
} 
