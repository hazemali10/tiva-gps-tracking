#ifndef LCD_H
#define LCD_H

#endif
// lcd functions
void delay(long d);
void printdata(unsigned char data);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_string(unsigned char *str,unsigned char len);
void lcd_init(void);