#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <Arduino.h>

#define MINRPM 750
#define MAXRPM 7000
#define MINSPEED 0
#define MAXSPEED 110
#define ACCEL 10

class SensorData
{
    const int potentiometerPin = A0;
    double speedRpmDiff_prcnt = 0;
    double mph = 0;
    int rpm = 0;

    void calcSpeed();
public:
    SensorData();
    void update();
    double *getMphByRef();
    int *getRpmByRef();
};

#endif