#ifndef GPIO_H
#define GPIO_H

#define GPIO_LED_ON     1
#define GPIO_LED_OFF    0
#define GPIO_SW_ON      0
#define GPIO_SW_OFF     1


typedef enum {
    SW1 = 4,
    SW2 = 0,
    LED_RED = 1,
    LED_BLUE = 2,
    LED_GREEN = 3
} GPIO_PIN;



void GPIO_setLedValue(GPIO_PIN, unsigned char);

unsigned char GPIO_getSwitchValue(GPIO_PIN);

void GPIO_initPortA(void);
void GPIO_initPortB(void);
void GPIO_initPortF(void);

#endif
