#ifndef Can_bus_H
#define Can_bus_H

#include "mcp2515_can.h"
#include "sensorData.h"

#define CAN_2515
#define CAN_BAUDRATE CAN_500KBPS

const int SPI_CS_PIN = 10;
const int CAN_INT_PIN = 2;


class Can_bus : public mcp2515_can
{
private:
    static bool receiveFlag;
    static uint8_t len;
    static uint8_t buf[8];

    SensorData* sensorData;

    void sendCurrentData(uint8_t pid);
    void sendVehicleData(uint8_t pid);
    static void CANBUS_ISR();
public:
    Can_bus();
    bool begin(SensorData*);
    void update();
    static void setReceiveFlag();
};


#endif