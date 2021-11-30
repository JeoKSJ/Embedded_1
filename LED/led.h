#ifndef _LED_LIBRARYH_
#define _LED_LIBRARYH_
int ledLibInit(void); // 초기화(이 라이브러리는 엘리디를 켜기 전에 반드시 한번 불러주어야 한다
int ledLibOnOff (int ledNumber, int onOff); // Led 켜기/끄기
int ledLibStatus(void); 
// 현재 Led 상태(이 함수를 호출시 현재 led 상태를 확인해준다. 만약 모든 led가 on시 0xff를 리턴하고 
//만약 모든 led가 꺼져있으면 0x00을 리턴한다 
//만약 0xAA가 리턴되면, (10101010) > LED는 4개만 켜져잇다
int ledLibExit(void); // Led 라이브러리 종료
//이 함수를 호출하면 led를 전부 끄고 driver를 close한다
int ledLibRaw(char ledwannabe);
//이 함수를 호출하면 ledwannabe에 맞게 8개의 led를 전부 제어한다. 예를 들어 ledLibRaw(0x80); 1개만 켜진다.
int ledLibBlink(int ledNumber, int nth, int msec); //1~8까지의 LED를 하다 골라서 N번 깜박임.주기는 MSEC
int ledLibMorseBlink(int ledNumber, int nth, int msecOn, int msecOff);
#define LED_DRV_NODE "/dev/periled"

#endif
