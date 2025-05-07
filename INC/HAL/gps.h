#ifndef GPS_H
#define GPS_H
#define PI  3.14159265358979323846

void GPS_read(void);
float GPS_getDistance (float currentLong , float currentLat , float destLong , float destLat);
float toRad(float angle);

#endif
