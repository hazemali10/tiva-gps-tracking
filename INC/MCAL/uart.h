#ifndef UART_H
#define UART_H


void UART5_init(void);
char UART5_isCharAvailable(void);
char UART5_getChar(void);
void UART5_receiveString(char* arr,char stopChar);
void UART5_write(char data);


void UART2_init(void);
char UART2_isCharAvailable(void);
char UART2_getChar(void);
void UART2_receiveString(char* arr, char stopChar);

#endif
