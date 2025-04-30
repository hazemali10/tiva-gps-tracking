#include "gpio.h"
#include "tm4c123gh6pm.h"


int main(void) {
    GPIO_initPortF();
    
    while (1)
    {
        if (GPIO_getSwitchValue(SW1) == GPIO_SW_ON)
        {
            GPIO_setLedValue(LED_RED, GPIO_LED_ON);
            GPIO_setLedValue(LED_BLUE, GPIO_LED_OFF);
            GPIO_setLedValue(LED_GREEN, GPIO_LED_OFF);
        } 
        else if (GPIO_getSwitchValue(SW2) == GPIO_SW_ON)
        {
            GPIO_setLedValue(LED_RED, GPIO_LED_OFF);
            GPIO_setLedValue(LED_BLUE, GPIO_LED_ON);
            GPIO_setLedValue(LED_GREEN, GPIO_LED_OFF);
        }
        else
        {
            GPIO_setLedValue(LED_RED, GPIO_LED_OFF);
            GPIO_setLedValue(LED_BLUE, GPIO_LED_OFF);
            GPIO_setLedValue(LED_GREEN, GPIO_LED_ON);
        }
    }
    
}
