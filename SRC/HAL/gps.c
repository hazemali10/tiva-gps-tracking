#include "gps.h"
#include "bit_utils.h"
#include <math.h>
#include "uart.h"
#include <string.h>
#define PI  3.14159265358979323846

char GPS[80];
char GPS_LogName[]="$GPRMS,";


const double EARTH_RADIUS =6371000;

void GPS_read(){

    char recievedChar;
    char flag = 1 ;

    do{
   
        flag =1;
        for (char i=0; i<7 ; i++){

  
            if( UART0_getChar() != GPS_LogName[i]){

                flag=0;
                break;
            }
        }
    }

    while (flag==0);   //Making sure that I recieved the correct GPS_LogName

    strcpy(GPS,"");   // Removing any rubbish in array 

    do{


        char fillGPScounter=0;
        recievedChar=UART0_getChar();
        GPS[fillGPScounter++] = recievedChar;
    }
    while(recievedChar!='*');
}

float toDegree(float angle){     //Converting coordinates to degree
int degree = (int) angle /100;
float minutes = angle -(float) degree*100;
return (degree + (minutes/60));
}

float toRad(float angle){      ////Converting degree to radian
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
