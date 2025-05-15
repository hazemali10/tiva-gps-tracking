#include "tm4c123gh6pm.h"
#include "systick.h"
#include "gpio.h"
#include "lcd.h"

#include <stdio.h>

void LCD_pulse(void) {
    GPIO_PORTA_DATA_R |= 0x20 ;
    systick_waitMs(2);
    GPIO_PORTA_DATA_R &= ~ (0x20);
    systick_waitMs(2);
}

void LCD_data(unsigned char data) {
    GPIO_PORTA_DATA_R |= 0x08 ;
    GPIO_PORTB_DATA_R &= ~(0xFF) ;
	GPIO_PORTB_DATA_R |= data ;
	LCD_pulse();
	systick_waitMs(5);
}

void LCD_cmd(unsigned char cmd) {
    GPIO_PORTA_DATA_R &= ~(0x08) ;
    GPIO_PORTB_DATA_R &= ~(0xFF) ;
	GPIO_PORTB_DATA_R |= cmd ;
	LCD_pulse();
	systick_waitMs(5);
}

void LCD_string(char *str, LCD_COMMAND cmd) {
    char i;

    if (cmd == UPPER_LINE) {
        LCD_cmd(UPPER_LINE);
    } else if (cmd == LOWER_LINE) {
        LCD_cmd(LOWER_LINE);
    }

    while (str[i] != '\0') {
        LCD_data(str[i]);
        LCD_cmd(INCREMENT_CURSOR);
        i++;
    }
}

void LCD_init(void) {
    
    GPIO_initPortA();
    GPIO_initPortB();
    LCD_cmd(0x0C);                          // Display On, Cursor Off
    systick_waitMs(1);
    LCD_cmd(0x38);                          // 2 lines, 5x7 matrix
    systick_waitMs(1);  
    LCD_cmd(CLEAR);                          // Clear display screen
    systick_waitMs(10);  
    LCD_cmd(INCREMENT_CURSOR);              // Increment cursor
    systick_waitMs(1);
}
