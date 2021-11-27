#ifndef _LED_H_
#define _LED_H_
int ledLibInit(void); // 초기화
int ledOnOff (int ledNum, int onOff); // Led 켜기/끄기
int ledStatus(void); // 현재 Led 상태
int ledLibExit(void); // Led 라이브러리 종료

#define LED_DRIVER_NAME "/dev/periled"

#endif
