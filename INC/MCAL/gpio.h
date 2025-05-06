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

// lcd functions
void delay(long d);
void printdata(unsigned char data);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_string(unsigned char *str,unsigned char len);
void lcd_init(void);

void GPIO_setLedValue(GPIO_PIN, unsigned char);

unsigned char GPIO_getSwitchValue(GPIO_PIN);

void GPIO_initPortF(void);

#endif
