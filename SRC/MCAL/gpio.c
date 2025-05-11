#include "tm4c123gh6pm.h"
#include "bit_utils.h"
#include "gpio.h"


void GPIO_setLedValue(GPIO_PIN pin, unsigned char ledState) {
    if (ledState == GPIO_LED_ON) {
        SET_BIT(GPIO_PORTF_DATA_R, pin);
    } else {
        CLR_BIT(GPIO_PORTF_DATA_R, pin);
    }
}

unsigned char GPIO_getSwitchValue(GPIO_PIN pin) {
    return GET_BIT(GPIO_PORTF_DATA_R, pin);
}

void GPIO_initPortF()
{
    SYSCTL_RCGCGPIO_R |= 0x20;                      // activate clock for Port F
    while((SYSCTL_PRGPIO_R & 0x20) == 0);           // wait for clock to stabilize

    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTF_CR_R |= 0x1F;                        // allow changes to PF4-0

    GPIO_PORTF_AMSEL_R &= ~0x1F;                    // disable analog function
    GPIO_PORTF_PCTL_R &= 0x00000000;                // GPIO clear bit PCTL
    
    GPIO_PORTF_DIR_R |= 0x0E;                       // PF3,PF2,PF1 output
    GPIO_PORTF_DIR_R &= ~0x11;                      // PF4,PF0 input

    GPIO_PORTF_AFSEL_R &= ~0x1F;                    // no alternate function
    GPIO_PORTF_PUR_R |= 0x11;                       // enable pull-up resistors on PF4,PF0
    GPIO_PORTF_DEN_R |= 0x1F;                       // enable digital pins PF4-PF0

    GPIO_PORTF_DATA_R &= ~0x0E;                     // clear data register LEDs
}
