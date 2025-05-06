#include "gpio.h"
#include "tm4c123gh6pm.h"


int main(void) {
    GPIO_initPortF();
    
    while (1)
    {
        if (GPIO_getSwitchValue(SW1) == GPIO_SW_ON)
        {
           GPIO_PORTF_DATA_R = 0x02;
        } 
        else if (GPIO_getSwitchValue(SW2) == GPIO_SW_ON)
        {
            GPIO_PORTF_DATA_R = 0x04;
        }
        else
        {
            GPIO_PORTF_DATA_R = 0x08;
        }
    }
    
}
