#ifndef LCD_H
#define LCD_H

typedef enum {
    UPPER_LINE = 0x80,
    LOWER_LINE = 0xC0,
    INCREMENT_CURSOR = 0x06,
    CLEAR = 0x01
} LCD_COMMAND;

void delay(long d);

void LCD_pulse(void);
void LCD_cmd(unsigned char cmd);
void LCD_init(void);

#endif
