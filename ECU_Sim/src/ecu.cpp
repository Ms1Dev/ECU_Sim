#include "ecu.h"

Ecu::Ecu()
{
    pinMode(potentiometerPin, INPUT);
}

void Ecu::update()
{
    if (lastUpdate + REFRESH_RATE < millis()) {
        unsigned int actualRefreshRate = millis() - lastUpdate;
        lastUpdate = millis();
        
        int potentiometerReading = analogRead(potentiometerPin);
        engineSpeed = map(potentiometerReading, 0, 1023, MINRPM, MAXRPM);
        double engineSpeedPrcnt = (1.0 / (MAXRPM - MINRPM)) * (engineSpeed - MINRPM);
        double speedPrcnt = (1.0 / MAXSPEED) * vehicleSpeed;
        speedRpmDiff_prcnt = engineSpeedPrcnt - speedPrcnt; 
        throttlePosition = engineSpeedPrcnt * 100;

        calcSpeed(actualRefreshRate);
        calcMAF(engineSpeedPrcnt, speedPrcnt);
        calcFuelRate();
    }
}


void Ecu::calcSpeed(unsigned int actualRefreshRate) 
{
    double secondsSinceLastUpdate = actualRefreshRate / 1000.0;
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


void Ecu::calcMAF(double engineSpeedPrcnt, double speedPrcnt) 
{
    MAF = (MAFMAX - MAFMIN) * engineSpeedPrcnt * speedPrcnt;
    if (MAF < MAFMIN) MAF = MAFMIN;
}

void Ecu::calcFuelRate() 
{
    double gramsPerSec = MAF / PETROL_STOICH_RATIO ;
    double mlPerSec = gramsPerSec * PETROL_GRAM_TO_ML;
    double mlPerHour = mlPerSec * 60 * 60;
    fuelRate = mlPerHour / 1000;
}


int Ecu::getVehicleSpeed()
{
    return (int) vehicleSpeed;
}

double Ecu::getEngineSpeed()
{
    return engineSpeed;
}

double Ecu::getMAF()
{
    return MAF;
}

int Ecu::getThrottlePosition()
{
    return throttlePosition;
}

double Ecu::getFuelRate()
{
    return fuelRate;
}
