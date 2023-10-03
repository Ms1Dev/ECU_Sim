#include <Arduino.h>
#include "display.h"
#include "sensorData.h"

Display display;
SensorData sensorData;

void setup() 
{
  pinMode(A0, INPUT);
  display.begin(sensorData.getMphByRef(), sensorData.getRpmByRef());
}

void loop() 
{
  sensorData.update();
  display.update();
  delay(500);
}
