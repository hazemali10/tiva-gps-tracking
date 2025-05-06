#include "lcd.h"
#include "tm4c123gh6pm.h"

void delay(long d);
void LCD_printData(unsigned char data);
void LCD_data(unsigned char data);
void LCD_cmd(unsigned char cmd);
void LCD_string(unsigned char *str,unsigned char len);
void LCD_init(void);
/*
    RS= PD0
    RW= PD1
    EN= PD2
    
    D0= PA7
    D1= PA6
    D2= PA5
    D3= PB4
    D4= PE5
    D5= PE4
    D6= PB1
    D7= PB0
*/




void LCD_gpioInit(){
    
    SYSCTL_RCGCGPIO_R |= 0x1B;
    while((SYSCTL_PRGPIO_R& 0x01)==0){};
    GPIO_PORTA_DEN_R |= 0xE0;
    GPIO_PORTB_DEN_R |= 0x13;
    GPIO_PORTD_DEN_R |= 0x07;
    GPIO_PORTE_DEN_R |= 0x30
    // direction 
    GPIO_PORTA_DIR_R |= 0xE0;
    GPIO_PORTB_DIR_R |= 0x13;
    GPIO_PORTD_DIR_R |= 0x07;
    GPIO_PORTE_DIR_R |= 0x30;

}

void delay(long d)
{
    while (d--){};
    
}

void LCD_printData(unsigned char data){
    if((data&0x01)==0x01)(GPIO_PORTA_DATA_R |= (1<<7) );
    else (GPIO_PORTA_DATA_R &= (~(1<<7)))

    if((data&0x02)==0x02)(GPIO_PORTA_DATA_R |= (1<<6) );
    else (GPIO_PORTA_DATA_R &= (~(1<<6)))

    if((data&0x04)==0x04)(GPIO_PORTB_DATA_R |= (1<<5) );
    else (GPIO_PORTA_DATB_R &= (~(1<<5)))
    
    if((data&0x08)==0x08)(GPIO_PORTA_DATA_R |= (1<<4) );
    else (GPIO_PORTA_DATA_R &= (~(1<<4)))

    if((data&0x10)==0x10)(GPIO_PORTE_DATA_R |= (1<<5) );
    else (GPIO_PORTE_DATA_R &= (~(1<<5)))

    if((data&0x20)==0x20)(GPIO_PORTE_DATA_R |= (1<<4) );
    else (GPIO_PORTE_DATA_R &= (~(1<<4)))

    if((data&0x40)==0x40)(GPIO_PORTB_DATA_R |= (1<<1) );
    else (GPIO_PORTB_DATA_R &= (~(1<<1)))

    if((data&0x80)==0x80)(GPIO_PORTB_DATA_R |= (1<<0) );
    else (GPIO_PORTB_DATA_R &= (~(1<<0)))
}

void LCD_data(unsigned char data){
    // passing 8 bit data
    printdata(data);
    GPIO_PORTD_DATA_R &= ~0x02;//turn off RW
    GPIO_PORTD_DATA_R |= 0x01;//turn on RS
    GPIO_PORTD_DATA_R |= 0x04 //turn on enable
    delay(10000);
    GPIO_PORTD_DATA_R &= ~(0x04) // turn off enable

}
void LCD_cmd(unsigned char cmd){// for instruction 
    // passing 8 bit data
    printdata(cmd);
    GPIO_PORTD_DATA_R &= ~0x02;//turn off RW
    GPIO_PORTD_DATA_R &= ~0x01;//turn on RS
    GPIO_PORTD_DATA_R |= 0x04 //turn on enable
    delay(10000);
    GPIO_PORTD_DATA_R &= ~(0x04) // turn off enable

}
void LCD_string(unsigned char *str,unsigned char len){

}