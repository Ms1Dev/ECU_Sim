#include "can_bus.h"
#include <SPI.h>


bool Can_bus::receiveFlag = false;
uint8_t Can_bus::len = 0;
uint8_t Can_bus::buf[8];

Can_bus::Can_bus() :
mcp2515_can(SPI_CS_PIN)
{
}


bool Can_bus::begin(SensorData* sensorData) 
{
    this->sensorData = sensorData;

    attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), Can_bus::CANBUS_ISR, FALLING); 

    for (int i = 0; i < 10; i++) {
        if (mcp2515_can::begin(CAN_BAUDRATE) == CAN_OK) return true;
        delay(100);
    }
    return false;
}


void Can_bus::update()
{
    if (receiveFlag) {
        receiveFlag = false;
        readMsgBuf(&len, buf);
        uint8_t pid = buf[2];
        sendResponse(pid);
    }
}


void Can_bus::sendResponse(uint8_t pid)
{
    uint8_t msgBuf[8];
    uint16_t data;
    uint8_t high_byte;
    uint8_t low_byte;

    switch (pid) {
    case 0:
        msgBuf[0] = 0x06;
        msgBuf[1] = 0x41;
        msgBuf[2] = 0x00;            
        msgBuf[3] = 0;
        msgBuf[4] = 0;
        msgBuf[5] = 0;
        msgBuf[6] = 0;
        msgBuf[7] = 0;
        break;
    case 12: // rpm
        data = 4 * sensorData->getEngineSpeed();
        low_byte = data & 0xFF;
        high_byte = data >> 8;

        msgBuf[0] = 0x04;
        msgBuf[1] = 0x41;
        msgBuf[2] = 0x0C;            
        msgBuf[3] = high_byte;
        msgBuf[4] = low_byte;
        msgBuf[5] = 0;
        msgBuf[6] = 0;
        msgBuf[7] = 0;
        break;
    case 13: // speed
        high_byte = sensorData->getVehicleSpeed();
        msgBuf[0] = 0x03;
        msgBuf[1] = 0x41;
        msgBuf[2] = 0x0D;            
        msgBuf[3] = high_byte;
        msgBuf[4] = 0;
        msgBuf[5] = 0;
        msgBuf[6] = 0;
        msgBuf[7] = 0;
        break;
    case 16: // MAF
        data = 100 * sensorData->getMAF();
        low_byte = data & 0xFF;
        high_byte = data >> 8;
        msgBuf[0] = 0x04;
        msgBuf[1] = 0x41;
        msgBuf[2] = 0x10;            
        msgBuf[3] = high_byte;
        msgBuf[4] = low_byte;
        msgBuf[5] = 0;
        msgBuf[6] = 0;
        msgBuf[7] = 0;
        break;
    case 17: // throttle pos
        high_byte = 255 * (sensorData->getThrottlePosition() / 100.0);
        msgBuf[0] = 0x03;
        msgBuf[1] = 0x41;
        msgBuf[2] = 0x11;            
        msgBuf[3] = high_byte;
        msgBuf[4] = 0;
        msgBuf[5] = 0;
        msgBuf[6] = 0;
        msgBuf[7] = 0;
        break;
    case 94: // fuel rate
        data = 20 * sensorData->getFuelRate();
        low_byte = data & 0xFF;
        high_byte = data >> 8;
        msgBuf[0] = 0x04;
        msgBuf[1] = 0x41;
        msgBuf[2] = 0x5E;            
        msgBuf[3] = high_byte;
        msgBuf[4] = low_byte;
        msgBuf[5] = 0;
        msgBuf[6] = 0;
        msgBuf[7] = 0;
        break;
    }
    sendMsgBuf(2024,0,8,msgBuf);
}


void Can_bus::CANBUS_ISR()
{
    receiveFlag = true;
}

