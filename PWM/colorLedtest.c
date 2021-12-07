#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define COLOR_LED_DEV_R_ "/sys/class/pwm/pwmchip0/"
#define COLOR_LED_DEV_G_ "/sys/class/pwm/pwmchip1/"
#define COLOR_LED_DEV_B_ "/sys/class/pwm/pwmchip2/"

#define PWM_EXPORT "export"
#define PWM_UNEXPORT "unexport"
#define PWM_DUTY "pwm0/duty_cycle"
#define PWM_PERIOD "pwm0/period"
#define PWM_ENABLE "pwm0/enable"

#define PWM_COLOR_R 0
#define PWM_COLOR_G 1
#define PWM_COLOR_B 2

#define PWM_PERIOD_NS 1000000 //ns. = 1ms = 1k
#include "colorLed.h"

int main(int argc, char *argv[])
{
    if(argc != 4)
    {
        printf("colorledtest.elf 0-100 0-100 0-100 \r\n");
        printf("ex) colorledtest.elf 100 100 100 ==> full white color \r\n");
        return 0;
    }
    pwmLedInit(); // 1. init
    pwmSetPercent(atoi(argv[1]),0); // 2-1. Set 1
    pwmSetPercent(atoi(argv[2]),1); // 2-2. Set 2
    pwmSetPercent(atoi(argv[3]),2); // 2-3. Set 3
    pwmInactiveAll(); // 3. Inactivate
    return 0;
}