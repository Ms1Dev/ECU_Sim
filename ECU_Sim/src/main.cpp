#include <Arduino.h>
#include "display.h"
#include "ecu.h"
#include "can_bus.h"


Display display;
Ecu ecu;
Can_bus can_bus;

void setup() 
{
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
}
