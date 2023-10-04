#include <Arduino.h>
#include "display.h"
#include "sensorData.h"

#define SERIALOUTPUT

#define REFRESH_RATE 4 //Hz
#define UPDATE_DELAY 1000 / REFRESH_RATE

Display display;
SensorData sensorData;

void setup() 
{
  #ifdef SERIALOUTPUT
  Serial.begin(9600);
  #endif

  pinMode(A0, INPUT);
  display.begin(sensorData.getMphByRef(), sensorData.getRpmByRef());
}

void loop() 
{
  sensorData.update();
  display.update();

  #ifdef SERIALOUTPUT
  Serial.println("------------------------------");
  Serial.print("Speed: ");
  Serial.println(sensorData.getVehicleSpeed());
  Serial.print("RPM: ");
  Serial.println(sensorData.getEngineSpeed());
  Serial.print("Throttle: ");
  Serial.println(sensorData.getThrottlePosition());
  Serial.print("MAF: ");
  Serial.println(sensorData.getMAF());
  Serial.print("Fuel Rate: ");
  Serial.println(sensorData.getFuelRate());
  #endif

  delay(UPDATE_DELAY);
}
