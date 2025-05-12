#include "uart.h"
#include "tm4c123gh6pm.h"
#include "bit_utils.h"

void UART5_init() {

		SET_BIT(SYSCTL_RCGCUART_R,5);       			    	//Enable UART5 clock
		while(GET_BIT(SYSCTL_PRUART_R,5)==0);   				//wait until UART5 clock is set

		SET_BIT(SYSCTL_RCGCGPIO_R,4);           				//Enable PORTE clock
		while (GET_BIT(SYSCTL_PRGPIO_R,4)==0);  				//wait until PORTE clock is set

		CLR(UART5_CTL_R, UART_CTL_UARTEN);      				//Disable UART

		UART5_IBRD_R=104;
		UART5_FBRD_R=11;

		SET(UART5_LCRH_R,UART_LCRH_WLEN_8);     				//Set wordlength = 8 bits
		SET(UART5_LCRH_R,UART_LCRH_FEN);        				//Enables FIFO

        SET(UART5_CTL_R, 0x301);

        SET(GPIO_PORTE_AFSEL_R, 0x30);
		CLR(GPIO_PORTE_PCTL_R ,0x000000FF);
		SET(GPIO_PORTE_PCTL_R, GPIO_PCTL_PE4_U5RX); 		//Set alternate fn of PE4
		SET(GPIO_PORTE_PCTL_R, GPIO_PCTL_PE5_U5TX); 		//Set alternate fn of PE5
		SET(GPIO_PORTE_DEN_R,0x30);                  		//Digital enable for PE4,PE5
        CLR(GPIO_PORTE_AMSEL_R, 0x30);
}

char UART5_isCharAvailable() {
    return ((UART5_FR_R & UART_FR_RXFE) != UART_FR_RXFE);
}

//Get char
char UART5_getChar() {
    while((UART5_FR_R & UART_FR_RXFE) != 0 );   //Checks Receiver FIFO is not empty
    return (char) GET_REG(UART5_DR_R);          //if not empty go get data
}

void UART5_receiveString(char* arr,char stopChar){
   char character;
   char i=0;

   while(1){
     character =UART5_getChar();
	 if(character == stopChar) {
		break;
	 }
	 arr[i++]=character;
   }
    arr[i] = '\0'; //Null terminates the string
}

void UART5_write(char data) {
    while((UART5_FR_R & UART_FR_TXFF) != 0);         // Wait while transmit FIFO is full (TXFF)
    UART5_DR_R = data;                                // Write the byte to data register
}


void UART2_init(void) {
    // 1. Enable clock for UART2
    SYSCTL_RCGCUART_R |= 0x04;

    // 2. Enable clock for PORTD (UART2 uses PD6=RX, PD7=TX)
    SYSCTL_RCGCGPIO_R |= 0x08;
    while ((SYSCTL_PRGPIO_R & 0x08) == 0) {};

    // 3. Disable UART2 before configuration
    UART2_CTL_R &= ~0x01;

    // 4. Set baud rate (Assuming system clock is 16 MHz)
    UART2_IBRD_R |= 325;  // Integer part
    UART2_FBRD_R |= 35;   // Fractional part (0.1667 * 64 + 0.5 = 11)

    // 5. Configure UART line control for 8-bit, no parity, 1-stop, enable FIFOs
    UART2_LCRH_R |= 0x70;

    // 6. Enable UART2, TXE, RXE
    UART2_CTL_R |= 0x301;

    // 7. Configure GPIO pins PD6 and PD7 for UART2
    GPIO_PORTD_AFSEL_R |= 0xC0;         // Enable alt function on PD6, PD7
    GPIO_PORTD_PCTL_R &= ~0xFF000000;   // Clear PCTL bits for PD6, PD7
    GPIO_PORTD_PCTL_R |=  0x11FFFFFF;   // Configure PD6, PD7 for UART2
    GPIO_PORTD_DEN_R   |= 0xC0;         // Digital enable on PD6, PD7
    GPIO_PORTD_AMSEL_R &= ~0xC0;        // Disable analog on PD6, PD7
}


char UART2_isCharAvailable() {
    return ((UART2_FR_R & UART_FR_RXFE) != UART_FR_RXFE);
}

//Get char
char UART2_getChar() {
    while((UART2_FR_R & UART_FR_RXFE) != 0 );   //Checks Receiver FIFO is not empty 
    return (char) GET_REG(UART2_DR_R);          //if not empty go get data
}

void UART2_receiveString(char* arr, char stopChar) {
   char character;
   char i = 0;

   while(1){
     character = UART2_getChar();
	 if(character == stopChar) {
		break;
	 }
	 arr[i++]=character;
   }
    arr[i] = '\0'; //Null terminates the string
}


