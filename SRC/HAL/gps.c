#include "gps.h"
#include "bit_utils.h"
#include "uart.h"

#include <string.h>
#include <stdlib.h>
#include <math.h>

#define PI  3.14159265358979323846

char GPS_logName[]="$GPRMS,";

//data fields 
char valid;
char latitude[15];
char NS;
char longitude[15];
char EW;
char speed[15];

float currentLat;
float currentLong;


void GPS_read(){

    char counter = 0 ; // number of gps data fields (after each comma)
    char i = 0 ; //char iterating through logname 
    char recievedChar;
    char flag = 1 ;//raised after each character data field 

    do {
        while (UART0_getChar() != GPS_logName[i]) 
        {
             // until a matching char is caught 
        }
        i++;
    } while (i != 7);  //Making sure GPS_LogName is correct and complete 


    while (1) {

        if (flag) { //if the received character is a comma it means the end of a data field has been reached so the counter is incremented.
            recievedChar = UART0_getChar(); // after each char flag = 1 to increment counter  
            if (recievedChar == ',') {
                counter++;
            }
        }

        switch (counter) {
            case 1:
                valid = UART0_getChar();
                break;
            case 2:
                UART0_receiveString(latitude, ',');
                counter++;
                flag = 0; // after each string flag = 0 counter is already incremented 
                break;
            case 3:
                NS = UART0_getChar();
                flag = 1; // after each char flag = 1 to increment counter 
                break;
            case 4:
                UART0_receiveString(longitude, ',');
                counter++;
                flag = 0;
                break;
            case 5:
                EW = UART0_getChar();
                flag = 1;
                break;
            case 6:
                UART0_receiveString(speed, ',');
                counter++;
                flag = 0;
                break;
        }

        if (counter == 7) break;

    }
    if(valid == 'A') { // Valid
        if(NS =='N')
            currentLat = atof(latitude);
        else
            currentLat = -atof(latitude);
        
        if(EW =='E') 
            currentLong = atof(longitude);
        else
            currentLong = -atof(longitude);
    }
}

        
float toRad(float angle){     //Converting coordinates to Rad
    int degree = (int) angle /100;
    float minutes = angle -(float) degree*100;
    return ((degree + (minutes/60))* PI /180);

}


float GPS_getDistance (float currentLong , float currentLat , float destLong , float destLat){

    //Get Radian Angle
    float currentLongRad= toRad(currentLong);
    float currentLatRad= toRad(currentLat);
    float destLongRad= toRad(destLong);
    float destLatRad= toRad(destLat);


    //Get Difference
    float LongDiff = destLongRad-currentLongRad;
    float LatDiff = destLatRad-currentLatRad;


    //Calculate Distance 
    float a = pow(sin(LatDiff/2),2) + cos(currentLatRad)*cos(destLatRad)* pow(sin(LongDiff/2),2); //Haversine Formula
    double c = 2 * atan2(sqrt(a),sqrt(1-a));
    return 950000 *c;

}
