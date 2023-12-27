#ifndef SENSORDATA_H
#define SENSORDATA_H

class SensorData
{
public:
    virtual int getVehicleSpeed() = 0;
    virtual double getEngineSpeed() = 0;
    virtual double getMAF() = 0;
    virtual int getThrottlePosition() = 0;
    virtual double getFuelRate() = 0;
    virtual int getCalculatedLoad() = 0;
    virtual int getIntakeTemperature() = 0;
    virtual int getIntakePressure() = 0;
};

#endif