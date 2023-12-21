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
    
    // pinMode(CAN_INT_PIN, INPUT);

    // attachInterrupt(digitalPinToInterrupt(CAN_INT_PIN), Can_bus::CANBUS_ISR, RISING); 

    for (int i = 0; i < 10; i++) {
        if (mcp2515_can::begin(CAN_BAUDRATE) == CAN_OK) return true;
        delay(100);
    }
    return false;
}


void Can_bus::update()
{
    if (CAN_MSGAVAIL == checkReceive()) {
        // receiveFlag = false;
        readMsgBuf(&len, buf);
        uint8_t pid = buf[2];
        sendResponse(pid);
    }
}


void Can_bus::sendResponse(uint8_t pid)
{
    uint8_t mode = 0x41; 
    uint8_t msgBuf[8];
    uint16_t data;

    msgBuf[1] = mode;
    msgBuf[2] = pid;

    switch (pid) {
    case 0: // Supported PIDS
        msgBuf[0] = 0x06;           
        msgBuf[3] = 0xFF;
        msgBuf[4] = 0xFF;
        msgBuf[5] = 0xFF;
        msgBuf[6] = 0xFF;
        break;
    case 0x20: // Supported PIDS
        msgBuf[0] = 0x06;           
        msgBuf[3] = 0xFF;
        msgBuf[4] = 0xFF;
        msgBuf[5] = 0xFF;
        msgBuf[6] = 0xFF;
        break;
    case 0x40: // Supported PIDS
        msgBuf[0] = 0x06;           
        msgBuf[3] = 0xFF;
        msgBuf[4] = 0xFF;
        msgBuf[5] = 0xFF;
        msgBuf[6] = 0xFF;
        break;
    case 0x0C: // rpm
        data = 4 * sensorData->getEngineSpeed();

        msgBuf[0] = 0x04;
        msgBuf[3] = data >> 8;
        msgBuf[4] = data & 0xFF;
        break;
    case 0x0D: // speed
        msgBuf[0] = 0x03;
        msgBuf[3] = sensorData->getVehicleSpeed();
        break;
    case 0x10: // MAF
        data = 100 * sensorData->getMAF();

        msgBuf[0] = 0x04;
        msgBuf[3] = data >> 8;
        msgBuf[4] = data & 0xFF;
        break;
    case 0x11: // throttle pos
        msgBuf[0] = 0x03;          
        msgBuf[3] = (255 * sensorData->getThrottlePosition()) / 100.0;
        break;
    case 0x5E: // fuel rate
        data = 20 * sensorData->getFuelRate();

        msgBuf[0] = 0x04;         
        msgBuf[3] = data >> 8;
        msgBuf[4] = data & 0xFF;
        break;
    }

    sendMsgBuf(2024,0,8,msgBuf);
}


// void Can_bus::CANBUS_ISR()
// {
//     receiveFlag = true;
// }

