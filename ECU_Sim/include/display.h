#ifndef Display_H
#define DISPLY_H

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "sensorData.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32 

#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C 

class Display : public Adafruit_SSD1306
{
private:
    SensorData* sensorData;
    const int REFRESH_RATE = 250;
    unsigned long lastUpdate = 0;
public:
    Display();
    void begin(SensorData*);
    void update();
};

#endif