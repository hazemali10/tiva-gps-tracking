#include "gps.h"
#include "bit_utils.h"
#include <math.h>
#include "uart.h"
#include <string.h>
#define PI  3.14159265358979323846

char GPS_LogName[]="$GPRMS,";
const double EARTH_RADIUS =6371000;

//data fields 
char valid;
char latitude[15];
char NS;
char longitude[15];
char EW;
char speed[15];

void GPS_read(){

    char counter = 0 ; // number of gps data fields (after each comma)
    char i = 0 ; //char iterating through logname 
    char recievedChar;
    char flag = 1 ;//raised after each character data field 

    do {
        while (UART0_recieveByte() != GPS_logName[i]) 
        {
             // until a matching char is caught 
        }
        i++;
    } while (i != 7);  //Making sure GPS_LogName is correct and complete 


    while (1) {

        if (flag) { //if the received character is a comma it means the end of a data field has been reached so the counter is incremented.
            recievedChar = UART0_recieveByte(); // after each char flag = 1 to increment counter  
            if (recievedChar == ',') {
                counter++;
            }
        }

        switch (counter) {
            case 1:
                Valid = UART0_recieveByte();
                break;
            case 2:
                UART0_recieveString(latitude, ',');
                counter++;
                flag = 0; // after each string flag = 0 counter is already incremented 
                break;
            case 3:
                NS = UART0_recieveByte();
                flag = 1; // after each char flag = 1 to increment counter 
                break;
            case 4:
                UART0_recieveString(longitude, ',');
                counter++;
                flag = 0;
                break;
            case 5:
                EW = UART0_recieveByte();
                flag = 1;
                break;
            case 6:
                UART0_recieveString(speed, ',');
                counter++;
                flag = 0;
                break;
        }

        if (counter == 7) break;
    }
}

 if((valid, "A") == 0) { // Valid
            if((NS, "N") == 0)
                currentLat = atof(latitude);
            else
                currentLat = -atof(latitude);
            
            if((EW, "E") == 0)
                currentLong = atof(longitude);
            else
                currentLong = -atof(longitude);
        }

        
float toDegree(float angle){     //Converting coordinates to degree
int degree = (int) angle /100;
float minutes = angle -(float) degree*100;
return (degree + (minutes/60));
}


float toRad(float angle){      //Converting degree to radian
return angle * PI /180;
}


float GPS_getDistance (float currentLong , float currentLat , float destLong , float destLat){


//Get Radian Angle
float currentLongRad= toRad(toDegree(currentLong));
float currentLatRad= toRad(toDegree(currentLat));
float destLongRad= toRad(toDegree(destLong));
float destLatRad= toRad(toDegree(destLat));


//Get Difference
float LongDiff = destLongRad-currentLongRad;
float LatDiff = destLatRad-currentLatRad;


//Calculate Distance 
float a = pow(sin(LatDiff/2),2) + cos(currentLatRad)*cos(destLatRad)* pow(sin(LongDiff/2),2); //Haversine Formula
double c = 2 * atan2(sqrt(a),sqrt(1-a));
return EARTH_RADIUS *c;

}
