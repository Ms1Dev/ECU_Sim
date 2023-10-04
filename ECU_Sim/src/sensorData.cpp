#include "sensorData.h"

SensorData::SensorData()
{
    pinMode(potentiometerPin, INPUT);
}

void SensorData::update()
{
    int potentiometerReading = analogRead(potentiometerPin);
    engineSpeed = map(potentiometerReading, 0, 1023, MINRPM, MAXRPM);
    double engineSpeedPrcnt = (1.0 / (MAXRPM - MINRPM)) * (engineSpeed - MINRPM);
    double speedPrcnt = (1.0 / MAXSPEED) * vehicleSpeed;
    speedRpmDiff_prcnt = engineSpeedPrcnt - speedPrcnt; 
    throttlePosition = engineSpeedPrcnt * 100;

    calcSpeed();
    calcMAF(engineSpeedPrcnt, speedPrcnt);
    calcFuelRate();
}


void SensorData::calcSpeed() 
{
    double secondsSinceLastUpdate = (millis() - lastUpdateMillis) / 1000.0;
    lastUpdateMillis = millis();
    double accel = ACCEL * secondsSinceLastUpdate;
    double speedChangeKPH = accel * 3.6;

    if ((speedRpmDiff_prcnt < -0.25 || engineSpeed < 775) && vehicleSpeed > 0) {
        vehicleSpeed -= speedChangeKPH;
    }
    else {
        vehicleSpeed += speedChangeKPH * speedRpmDiff_prcnt;
    }

    if (vehicleSpeed < 0) {
        vehicleSpeed = 0;
    }
}


void SensorData::calcMAF(double engineSpeedPrcnt, double speedPrcnt) 
{
    MAF = (MAFMAX - MAFMIN) * engineSpeedPrcnt * speedPrcnt;
    if (MAF < MAFMIN) MAF = MAFMIN;
}

void SensorData::calcFuelRate() 
{
    double gramsPerSec = MAF / PETROL_STOICH_RATIO ;
    double mlPerSec = gramsPerSec * PETROL_GRAM_TO_ML;
    double mlPerHour = mlPerSec * 60 * 60;
    fuelRate = mlPerHour / 1000;
}


double *SensorData::getMphByRef() 
{
    return &vehicleSpeed;
}

double *SensorData::getRpmByRef() 
{
    return &engineSpeed;
}

int SensorData::getVehicleSpeed()
{
    return (int) vehicleSpeed;
}

double SensorData::getEngineSpeed()
{
    return engineSpeed;
}

double SensorData::getMAF()
{
    return MAF;
}

int SensorData::getThrottlePosition()
{
    return throttlePosition;
}

double SensorData::getFuelRate()
{
    return fuelRate;
}
