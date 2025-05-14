#include "tm4c123gh6pm.h"
#include "systick.h"

#include <stdint.h>

void systick_init (void) {
    NVIC_ST_CTRL_R=SYSTICK_ENABLE_CLR; //disable timer
    NVIC_ST_RELOAD_R=SYSTICK_Reload_MAX; //number counts
    NVIC_ST_CURRENT_R=SYSTICK_CURRENT_CLR;
    NVIC_ST_CTRL_R=SYSTICK_ENABLE; // enable timer
    while((NVIC_ST_CTRL_R&SYSTICK_COUNT_FLAG)==0);
}
    
void systick_wait(uint32_t delay) {
    NVIC_ST_RELOAD_R=delay-1; //number counts
    while((NVIC_ST_CTRL_R&SYSTICK_COUNT_FLAG)==0);
}

void systick_waitMs(uint32_t delay) {
    unsigned long i;
    for (i=0;i<delay;i++)
    {
        systick_wait(16000); //wait 1 milliseconds
    }
}
