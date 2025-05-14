#ifndef LCD_H
#define LCD_H
// lcd functions
void delay(long d);
void LCD_printData(unsigned char data);
void LCD_data(unsigned char data);
void LCD_cmd(unsigned char cmd);
void LCD_string(unsigned char *str,unsigned char len);
void LCD_init(void);
void LCD_gpioInit();
#endif
