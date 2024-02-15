#include <Arduino.h>
#include "display.h"
#include "ecu.h"
#include "can_bus.h"
#include "mode_select.h"
#include "start_stop_btn.h"


Display display;
Ecu ecu;
Can_bus can_bus;
Mode_select mode_select;
StartStopBtn startStopBtn(3);

void setup() 
{
  ecu.begin();
  display.begin(&ecu);
  mode_select.begin();
  startStopBtn.begin();

  int mode = mode_select.getMode();

  display.clearDisplay();
  display.setCursor(0,0);

  if (can_bus.begin(&ecu, mode)) {
    display.println(F("CAN BUS init success"));
  }
  else {
    display.println(F("CAN BUS init fail"));
  }

  display.display();
  delay(2000);
}

void loop() 
{
  ecu.update();
  display.update();
  can_bus.update();
  if (startStopBtn.update()) {
    ecu.startStop();
  }
}
