#include <Arduino.h>
#include "display.h"
#include "ecu.h"
#include "can_bus.h"


// #define SERIALOUTPUT

Display display;
Ecu ecu;
Can_bus can_bus;

void setup() 
{
  #ifdef SERIALOUTPUT
  Serial.begin(9600);
  #endif

  pinMode(A0, INPUT);

  display.begin(&ecu);

  display.clearDisplay();
  display.setCursor(0,0);

  if (can_bus.begin(&ecu)) {
    display.println("CAN BUS init success");
  }
  else {
    display.println("CAN BUS init fail");
  }

  display.display();
  delay(2000);
}

void loop() 
{
  ecu.update();
  display.update();
  can_bus.update();

  #ifdef SERIALOUTPUT
  Serial.println("------------------------------");
  Serial.print("Speed: ");
  Serial.println(ecu.getVehicleSpeed());
  Serial.print("RPM: ");
  Serial.println(ecu.getEngineSpeed());
  Serial.print("Throttle: ");
  Serial.println(ecu.getThrottlePosition());
  Serial.print("MAF: ");
  Serial.println(ecu.getMAF());
  Serial.print("Fuel Rate: ");
  Serial.println(ecu.getFuelRate());
  #endif
}
