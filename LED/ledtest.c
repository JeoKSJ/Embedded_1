#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <ctype.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
// #define LED_DRIVER_NAME	"/dev/periled"
#include "led.h" // LED 헤더파일을 참조(과정 단순화)

/* 바꾸기 이전 버전(pdf 내용 그대로)
int main(int argc, char **argv)
{
    unsigned int data = 0;
    int fd;
    if(argc < 2) // argc 인수 값이 2보다 작을 시 에러 출력
    {
        perror("Args number is less than 2\n"); return 1;
    }
    data = strtol(argv[1],NULL,16); //String을 16진수로 가정하고 integer형으로 변환
    printf("wrate data : 0x%X\n", data);
    // 인수는 적어도 1은 받아야 함. LED 제어 bit

    fd = open(LED_DRIVER_NAME,O_RDWR); // "/dev/periled"를 열고 읽어옴
    if(fd < 0)
    {
        perror("driver (//dev/cnled)open error.\n"); return 1;
    }
    // "/dev/periled" 장치 open

    write(fd, &data, 4); // 내용을 "/dev/periled"에 저장

    close(fd); // LED_DRIVER_NAME을 닫음
    return 0;
    // 인수로 받은 LED 제어 값을 드라이버에 쓰는 것으로 종료.
}
*/
int main(int argc, char **argv)
{    
   ledLibInit();
   ledLibRaw(0xFF);
   sleep(1);
   ledLibRaw(0xAA);
   sleep(1);
   ledLibRaw(0x55);
   sleep(1);
   ledLibRaw(0x0);
 int i=0;
for(i=0;i<8;i++)
{
  ledLibOnOff(i,1);
  printf("0x%02X--OK?  \r\n",ledLibStatus());
  sleep(1);
  ledLibOnOff(i,0);
  sleep(1);


}



   ledLibBlink(1,10,500);
   ledLibMorseBlink(2,3,500,500);
   ledLibMorseBlink(2,3,1500,500);
   ledLibMorseBlink(2,3,500,500);

   sleep(2);
   ledLibExit();
    



    //unsigned int data = 0;
    //if(argc < 2) // argc 인수 값이 2보다 작을 시 에러 출력
    //{
     //   perror("Args number is less than 2\n"); return 1;
   // }
   // data = strtol(argv[1],NULL,16); //String을 16진수로 가정하고 integer형으로 변환
   // printf("wrate data : 0x%X\n", data);
    // 인수는 적어도 1은 받아야 함. LED 제어 bit
    
    //ledLibInit(); // LEDStatus initialize to Zero(0)
    //if(ledLibInit == -1) // Initialize failed(-1)
   // {
   //     perror("driver (//dev/cnled)open error.\n"); return 1;
    //}
    // "/dev/periled" Open failed
   // ledOnOff(data, 1); // LEDStatus shift opeator(1 << data)
   // ledLibExit(); // Close LEDStatus
    
   // return 0;
    // 인수로 받은 LED 제어 값을 드라이버에 쓰는 것으로 종료.
}

