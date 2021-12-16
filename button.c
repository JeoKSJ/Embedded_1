#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linux/input.h>
#include <unistd.h> // for open/close
#include <fcntl.h> // for O_RDWR
#include <sys/ioctl.h> // for ioctl
#include <sys/msg.h>
#include <pthread.h>
#include "button.h"
// first read input device
#define INPUT_DEVICE_LIST "/dev/input/event" //실제 디바이스 드라이버 노드파일: 뒤에 숫자가 붙음., ex)/dev/input/event5
#define PROBE_FILE "/proc/bus/input/devices" //PPT에 제시된 "이 파일을 까보면 event? 의 숫자를 알수 있다"는 바로 그 파일
#define HAVE_TO_FIND_1 "N: Name=\"ecube-button\"\n"
#define HAVE_TO_FIND_2 "H: Handlers=kbd event"


#include "button.h"

struct input_event stEvent;
char inputDevPath[200] = {0, };

static  pthread_t  buttonTh_id; 
BUTTON_MSG_T TxDataButton; 
static int fp = 0; 

static int msgID=77 ; 
int hi;
int probeButtonPath(char *newPath)
{

int returnValue = 0; //button에 해당하는 event#을 찾았나?
int number = 0; //찾았다면 여기에 집어넣자
FILE *fp = fopen(PROBE_FILE,"rt"); //파일을 열고

while(!feof(fp)) //끝까지 읽어들인다.
{
char tmpStr[200]; //200자를 읽을 수 있게 버퍼
fgets(tmpStr,200,fp); //최대 200자를 읽어봄
//printf ("%s",tmpStr);
if (strcmp(tmpStr,HAVE_TO_FIND_1) == 0)
{
printf("YES! I found!: %s\r\n", tmpStr);
returnValue = 1; //찾음
}


if (
(returnValue == 1) && //찾은 상태에서
(strncasecmp(tmpStr, HAVE_TO_FIND_2,
strlen(HAVE_TO_FIND_2)) == 0) //Event??을 찾았으면
)
{
printf ("-->%s",tmpStr);
printf("\t%c\r\n",tmpStr[strlen(tmpStr)-3]);
number = tmpStr[strlen(tmpStr)-3] - '0';
//Ascii character '0'-'9' (0x30-0x39)
//to interger(0)
break;
}
}
fclose(fp);
if (returnValue == 1)
sprintf (newPath,"%s%d",INPUT_DEVICE_LIST,number);
return returnValue;
}


void* buttonThFunc()  //쓰레드는 같은 주소공간을 공유한다.
 {
   
while (1) {
  hi = read(fp, &stEvent, sizeof (stEvent)); //button에 대응하는 event #number의 드라이버 노드 파일을 읽는다. stEvent의 크기는 키드사에 이미 제공되어있다.
if(hi != sizeof(stEvent))
{
  continue;
}         

if ( stEvent.type == EV_KEY)
{
printf("EV_KEY(");
switch(stEvent.code)
{
case KEY_VOLUMEUP: TxDataButton.keyInput=5; break; // 5
case KEY_HOME: TxDataButton.keyInput=0; break; // 1
case KEY_SEARCH: TxDataButton.keyInput=2; break; // 3
case KEY_BACK: TxDataButton.keyInput=1; break; // 2
case KEY_MENU: TxDataButton.keyInput=4;  break; // 4
case KEY_VOLUMEDOWN: TxDataButton.keyInput=6; break; // 6

default: break;
}
if ( stEvent.value ) 
{printf("pressed\n");
TxDataButton.pressed = 1;
TxDataButton.messageNum = 77;
msgsnd(msgID, &TxDataButton, sizeof(TxDataButton)-sizeof(TxDataButton.messageNum),0); //필요한 정보만 보내기



}
else 
{
TxDataButton.pressed = 0;
printf("released\n");


}

} 
else;


}





}























int buttonInit()
{



if ( probeButtonPath(inputDevPath) == 0)
{
printf ("ERROR! File Not Found!\r\n");
printf ("Did you insmod?\r\n");
return 0;
}
printf ("inputDevPath: %s\r\n", inputDevPath);
fp = open(inputDevPath, O_RDONLY);

msgID = msgget (MESSAGE_ID, IPC_CREAT|0666);
if (msgID == -1) //만약 메시지큐 식별자각 -1을 가진다면
{
    printf("Cannot get msgId Return!\r\n"); // 메시지큐id를 얻을수없다고 출력한다.
    return -1; //-1을 return한다.
}

pthread_create(&buttonTh_id, NULL, buttonThFunc, NULL);



return 1;
}







int buttonExit(void) 
  {
          pthread_exit(&buttonTh_id);
          close(fp);
  }



