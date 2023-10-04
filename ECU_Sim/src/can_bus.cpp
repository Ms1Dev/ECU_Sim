#include "can_bus.h"
#include <SPI.h>


bool Can_bus::receiveFlag = false;
uint8_t len = 0;


Can_bus::Can_bus() :
mcp2515_can(SPI_CS_PIN)
{
}


bool Can_bus::begin(SensorData* sensorData) 
{
    this->sensorData = sensorData;

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
        sendMessage(pid);
    }
}


void Can_bus::sendMessage(uint8_t pid)
{
    uint8_t msgBuf[8];
    uint16_t data;
    uint8_t high_byte;
    uint8_t low_byte;

    switch (pid) {
    case 0:
        msgBuf[0] = 6;
        msgBuf[1] = 65;
        msgBuf[2] = 0;            
        msgBuf[3] = 255;
        msgBuf[4] = 255;
        msgBuf[5] = 255;
        msgBuf[6] = 255;
        msgBuf[7] = 170;
        break;
    case 12: // rpm
        data = 4 * sensorData->getEngineSpeed();
        low_byte = data & 0xFF;
        high_byte = data >> 8;

        msgBuf[0] = 4;
        msgBuf[1] = 65;
        msgBuf[2] = 12;            
        msgBuf[3] = high_byte;
        msgBuf[4] = low_byte;
        msgBuf[5] = 170;
        msgBuf[6] = 170;
        msgBuf[7] = 170;
        break;
    case 13: // speed
        high_byte = sensorData->getVehicleSpeed();
        msgBuf[0] = 3;
        msgBuf[1] = 65;
        msgBuf[2] = 13;            
        msgBuf[3] = high_byte;
        msgBuf[4] = 170;
        msgBuf[5] = 170;
        msgBuf[6] = 170;
        msgBuf[7] = 170;
        break;
    case 16: // MAF
        data = 100 * sensorData->getMAF();
        low_byte = data & 0xFF;
        high_byte = data >> 8;
        msgBuf[0] = 4;
        msgBuf[1] = 65;
        msgBuf[2] = 16;            
        msgBuf[3] = high_byte;
        msgBuf[4] = low_byte;
        msgBuf[5] = 170;
        msgBuf[6] = 170;
        msgBuf[7] = 170;
        break;
    case 17: // throttle pos
        high_byte = sensorData->getThrottlePosition();
        msgBuf[0] = 3;
        msgBuf[1] = 65;
        msgBuf[2] = 17;            
        msgBuf[3] = high_byte;
        msgBuf[4] = 170;
        msgBuf[5] = 170;
        msgBuf[6] = 170;
        msgBuf[7] = 170;
        break;
    case 94: // fuel rate
        data = 20 * sensorData->getFuelRate();
        low_byte = data & 0xFF;
        high_byte = data >> 8;
        msgBuf[0] = 4;
        msgBuf[1] = 65;
        msgBuf[2] = 94;            
        msgBuf[3] = high_byte;
        msgBuf[4] = low_byte;
        msgBuf[5] = 170;
        msgBuf[6] = 170;
        msgBuf[7] = 170;
        break;
    }
    sendMsgBuf(0,0,8,msgBuf);
}


void Can_bus::setReceiveFlag() 
{
    receiveFlag = true;
}


void MCP2515_ISR() 
{
    Can_bus::setReceiveFlag();
}