#include "lcd.h"
#include "gps.h"

#include "systick.h"
#include "uart.h"
#include "gpio.h"
#include "tm4c123gh6pm.h"

#include <stdio.h> 

char latString[15];
char longString[15];

extern float currentLat;
extern float currentLong;

typedef struct {
  float latitude;
  float longitude;
} Location;

Location locations[8] = {
  {30.03851318, 31.16820557},  // Hall A
  {30.03864746, 31.16667236},  // Kharasana
  {30.03818604, 31.16706299},  // Credit
  {30.03883545, 31.16815430},  // Mosque
  {30.037916, 31.167437},      // Auto Workshop
  {30.038046, 31.167864},      // Loban
  {30.038204, 31.168348},      // Hall C
  {30.039341, 31.167074}       // Fountain
};

char* locationNames[] = {"Hall A", "Kharasana", "Credit", "Mosque", "Auto Workshop", "Loban", "Hall C", "Fountain"};

int main() {

  GPIO_initPortF();
  UART2_init();
  UART5_init();
	systick_init();

  LCD_init();

	while(1) {
    float minDistance = 9999;
    // char distanceString[15];
    char i;
    char minLocationIndex;
    float distance;

    GPS_read();

    while (currentLat == 0.0f) {
      GPS_read();
      LCD_string("Loading.  ", UPPER_LINE);
      systick_waitMs(500);
      LCD_string("Loading.. ", UPPER_LINE);
      systick_waitMs(500);
      LCD_string("Loading...", UPPER_LINE);
      systick_waitMs(500);
    }

    sprintf(latString, "%.6f", currentLat);
    sprintf(longString, "%.6f", currentLong);

    LCD_cmd(CLEAR);
    LCD_string("Latitude:", UPPER_LINE);
    LCD_string(latString, LOWER_LINE);

    systick_waitMs(5000);

    LCD_cmd(CLEAR);
    LCD_string("Longitude:", UPPER_LINE);
    LCD_string(longString, LOWER_LINE);

    systick_waitMs(5000);

    for (i = 0; i < 8; i++) {
      distance = GPS_getDistance(currentLong, currentLat, locations[i].longitude, locations[i].latitude);
      
      // sprintf(distanceString, "%.4f", distance);
      
      // LCD_cmd(CLEAR);
      // LCD_string(locationNames[i], UPPER_LINE);
      // LCD_string(distanceString, LOWER_LINE);

      // systick_waitMs(3000);

      if (distance < minDistance) {
        minDistance = distance;
        minLocationIndex = i;
      }
    }
    
    
    // sprintf(distanceString, "%.4f", minDistance);
    
    // LCD_cmd(CLEAR);
    // LCD_string(locationNames[minLocationIndex], UPPER_LINE);
    // LCD_string(distanceString, LOWER_LINE);

    // systick_waitMs(5000);
		
    

    LCD_cmd(CLEAR);
    LCD_string("Closest Area:", UPPER_LINE);
    LCD_string(locationNames[minLocationIndex], LOWER_LINE);

    systick_waitMs(5000);
  }

}
