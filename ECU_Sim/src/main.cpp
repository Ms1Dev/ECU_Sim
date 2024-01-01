#include <Arduino.h>
#include "display.h"
#include "ecu.h"
#include "can_bus.h"
#include "mode_select.h"


Display display;
Ecu ecu;
Can_bus can_bus;
Mode_select mode_select;

void setup() 
{
  ecu.begin();
  display.begin(&ecu);
  mode_select.begin();

  int mode = mode_select.getMode();

  display.clearDisplay();
  display.setCursor(0,0);

  if (can_bus.begin(&ecu, mode)) {
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
