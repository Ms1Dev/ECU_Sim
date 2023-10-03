#include "sensorData.h"

SensorData::SensorData()
{
    pinMode(potentiometerPin, INPUT);
}

void SensorData::update()
{
    int potentiometerReading = analogRead(potentiometerPin);
    rpm = map(potentiometerReading, 0, 1023, MINRPM, MAXRPM);
    double rpmPrcnt = (1.0 / (MAXRPM - MINRPM)) * (rpm - MINRPM);
    double speedPrcnt = (1.0 / MAXSPEED) * mph;
    speedRpmDiff_prcnt = rpmPrcnt - speedPrcnt; 

    calcSpeed();
}

void SensorData::calcSpeed() {
    if ((speedRpmDiff_prcnt < -0.2 || rpm < 775) && mph > 0) {
        mph -= ACCEL;
    }
    else {
        mph += ACCEL * speedRpmDiff_prcnt;
    }

    if (mph < 0) {
        mph = 0;
    }
}

double *SensorData::getMphByRef() 
{
    return &mph;
}

int *SensorData::getRpmByRef() 
{
    return &rpm;
}