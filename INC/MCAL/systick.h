#ifndef SYSTICK_H
#define SYSTICK_H

#include "stdint.h"

#define SYSTICK_CURRENT_CLR     0
#define SYSTICK_ENABLE_CLR      0
#define SYSTICK_ENABLE          0X05
#define SYSTICK_COUNT_FLAG      0X00010000
#define SYSTICK_Reload_MAX      0x00FFFFFF


void systick_init (void);
void systick_wait(uint32_t delay);
void systick_waitMs(uint32_t delay);

#endif
