#ifndef ECU_H
#define ECU_H

#include <Arduino.h>
#include "sensorData.h"

#define MINRPM 750
#define MAXRPM 7000
#define MINSPEED 0
#define MAXSPEED 150
#define MAFMIN 2.0
#define MAFMAX 150.0
#define ACCEL 5 // m/s^2
#define PETROL_STOICH_RATIO 14.7
#define PETROL_GRAM_TO_ML 1.35
#define INTAKEPRESSURE_MIN 33
#define INTAKEPRESSURE_MAX 100
#define INTAKE_TEMPERATURE 25 + 273

class Ecu : public SensorData
{
    const int potentiometerPin = A0;
    double speedRpmDiff_prcnt = 0;
    unsigned long lastUpdateMillis = 0;
    const int REFRESH_RATE = 250;
    unsigned long lastUpdate = 0;
    bool engineRunning = false;
    
    double vehicleSpeed = 0; // kmh
    double engineSpeed = 0; // rpm
    double MAF = 0; // g/s
    int throttlePosition = 0; // %
    double fuelRate = 0; // L/h
    int intakePressure = 0; // kPa
    int intakeTemperature = INTAKE_TEMPERATURE; // kelvin
    int engineLoad = 0; // %

    void calcSpeed(unsigned int actualRefreshRate);
    void calcMAF(double engineSpeedPrcnt, double speedPrcnt);
    void calcIntakePressure(double engineSpeedPrcnt);
    void calcEngineLoad();
    void calcFuelRate();
public:
    Ecu();
    void begin();
    void update();
    int getVehicleSpeed();
    double getEngineSpeed();
    double getMAF();
    int getThrottlePosition();
    int getIntakePressure();
    int getIntakeTemperature();
    int getCalculatedLoad();
    double getFuelRate();
    void startStop();
};

#endif