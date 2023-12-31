#include "display.h"
#include <Arduino.h>

Display::Display() :
Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{  
}

void Display::begin(SensorData* sensorData) 
{
  this->sensorData = sensorData;
  Adafruit_SSD1306::begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  setTextSize(1); 
  setTextColor(SSD1306_WHITE); 
}

void Display::update() 
{
  if (lastUpdate + REFRESH_RATE < millis()) {
    lastUpdate = millis();
    clearDisplay();
    setCursor(0,0);       
    print(F("Speed: "));
    print(sensorData->getVehicleSpeed());
    println(F(" km/h"));
    print(F("  RPM: "));
    println(sensorData->getEngineSpeed());
    display();
  }
}