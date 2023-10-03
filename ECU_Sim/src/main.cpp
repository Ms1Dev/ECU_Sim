#include <Arduino.h>
#include "display.h"

Display display;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  display.begin();
}

void loop() {
  Serial.println(analogRead(A0));
  delay(500);
}
