#include "uart.h"
#include "tm4c123gh6pm.h"
#include "bit_utils.h"

void UART0_init(){

		SET_BIT(SYSCTL_RCGCUART_R,0);       			    	//Enable UART0 clock
		while(GET_BIT(SYSCTL_PRUART_R,0)==0);   				//wait until UART0 clock is set

		SET_BIT(SYSCTL_RCGCGPIO_R,0);           				//Enable PORTA clock
		while (GET_BIT(SYSCTL_PRGPIO_R,0)==0);  				//wait until PORTA clock is set

		CLR(UART0_CTL_R, UART_CTL_UARTEN);      				//Disable UART

		UART0_IBRD_R=104;
		UART0_FBRD_R=11;

		SET(UART0_LCRH_R,UART_LCRH_WLEN_8);     				//Set wordlength = 8 bits
		SET(UART0_LCRH_R,UART_LCRH_FEN);        				//Enables FIFO

		CLR(GPIO_PORTA_PCTL_R ,0x000000FF);
		SET(GPIO_PORTA_PCTL_R, GPIO_PCTL_PA0_U0RX); 		//Set alternate fn of PA0
		SET(GPIO_PORTA_PCTL_R, GPIO_PCTL_PA1_U0TX); 		//Set alternate fn of PA1
		SET(GPIO_PORTA_DEN_R,0x3);                  		//Didital enable for PA0,PA1
}

char UART0_isCharAvailable(){
    return ((UART0_FR_R & UART_FR_RXFE) == UART_FR_RXFE);
}

//Get char
char UART0_getChar(){
    while((UART0_FR_R & UART_FR_RXFE) != 0 );   //Checks Receiver FIFO is not empty 
    return (char) GET_REG(UART0_DR_R);          //if not empty go get data
}

void UART0_receiveString(char * arr,char stopChar){
   char character;
   int i=0;

   while(1){
     character =UART0_getChar();
	 if(character == stopChar){
		break;
	 }
	 arr[i++]=character;
   }
    arr[i]="\0"; //Null terminates the string
}


