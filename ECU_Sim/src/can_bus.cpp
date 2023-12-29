#include "can_bus.h"
#include <SPI.h>
#include "modes.h"


uint8_t Can_bus::len = 0;
uint8_t Can_bus::buf[8];


Can_bus::Can_bus() :
mcp2515_can(SPI_CS_PIN)
{}


bool Can_bus::begin(SensorData* sensorData, int mode) 
{
    this->sensorData = sensorData;
    modes::OBD_Mode obd_mode = modes::obd_modes[mode];

    for (int i = 0; i < obd_mode.pidCount; i++) {
        addSupportedPid(obd_mode.supportedPids[i]);
    }

    uint8_t buff[8];
    getSupportedPidResponse(0x00, buff);

    for (int i = 0; i < 10; i++) {
        if (mcp2515_can::begin(CAN_BAUDRATE) == CAN_OK) return true;
        delay(100);
    }
    return false;
}


void Can_bus::addSupportedPid(uint8_t pid)
{
    uint8_t shiftedPid = pid -1;
    uint8_t byteIndex = shiftedPid / 8;
    uint8_t bitIndex = shiftedPid % 8;
    supportedPids[byteIndex] |= (1 << (7 - bitIndex));
}


void Can_bus::getSupportedPidResponse(uint8_t pid, uint8_t *msgBuf)
{
    uint8_t startIndex = pid / 0x20;
    msgBuf[0] = 0x06;           
    for (int i = 0; i < 4; i++) {
        msgBuf[3 + i] = supportedPids[startIndex + i];
    }
}

void Can_bus::getDataResponse(uint8_t pid, uint8_t *msgBuf)
{
    uint16_t data;
    switch (pid) {
            case 0x04: // calculated engine load
                data = 255 * sensorData->getCalculatedLoad() / 100.0 + 0.5; 

                msgBuf[0] = 0x04;
                msgBuf[3] = data;
                break;
            case 0x0B: // intake pressure
                msgBuf[0] = 0x04;
                msgBuf[3] = sensorData->getIntakePressure();
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
            case 0x0F: // intake temperature
                msgBuf[0] = 0x04;
                msgBuf[3] = sensorData->getIntakeTemperature() + 40;
                break;
            case 0x10: // MAF
                data = 100 * sensorData->getMAF();

                msgBuf[0] = 0x04;
                msgBuf[3] = data >> 8;
                msgBuf[4] = data & 0xFF;
                break;
            case 0x11: // throttle pos
                msgBuf[0] = 0x03;          
                msgBuf[3] = (255 * sensorData->getThrottlePosition()) / 100.0 + 0.5;
                break;
            case 0x5E: // fuel rate
                data = 20 * sensorData->getFuelRate();

                msgBuf[0] = 0x04;         
                msgBuf[3] = data >> 8;
                msgBuf[4] = data & 0xFF;
                break;
            case 0x66: // Alternative MAF
                data = 32 * sensorData->getMAF();

                msgBuf[0] = 0x07;
                msgBuf[3] = 1;
                msgBuf[6] = data >> 8;
                msgBuf[7] = data & 0xFF;
                break;
        }
}

void Can_bus::update()
{
    if (CAN_MSGAVAIL == checkReceive()) {
        // receiveFlag = false;
        readMsgBuf(&len, buf);
        uint8_t mode = buf[1];
        uint8_t pid = buf[2];

        switch (mode)
        {
        case 1:
            sendCurrentData(pid);
            break;
        case 9:
            sendVehicleData(pid);
            break;
        }
    }
}


void Can_bus::sendCurrentData(uint8_t pid)
{
    uint8_t mode = 0x41; 
    const int buflen = 8;
    uint8_t msgBuf[buflen];
    
    msgBuf[1] = mode;
    msgBuf[2] = pid;

    if (pid % 0x20 == 0) {
        getSupportedPidResponse(pid, msgBuf);
    }
    else {
        getDataResponse(pid, msgBuf);
    }

    sendMsgBuf(2024,0,buflen,msgBuf);
}


void Can_bus::sendVehicleData(uint8_t pid)
{
    if (pid != 0x02) return;

    uint8_t msg1[8] = {0x10, 0x13, 0x49, 2, '1', 'F', 'A', 'F'};
    uint8_t msg2[8] = {0x21, 'P', '5', '3', 'U', 'X', '4', 'A'};
    uint8_t msg3[8] = {0x22, '1', '6', '2', '7', '5', '7', 0};

    sendMsgBuf(2024,0,8,msg1);
    sendMsgBuf(2024,0,8,msg2);
    sendMsgBuf(2024,0,8,msg3);
}
