#include "display.h"


Display::Display() :
Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{  
}

void Display::begin(double* vehicleSpeed, double* engineSpeed) 
{
  this->vehicleSpeed = vehicleSpeed;
  this->engineSpeed = engineSpeed;
  Adafruit_SSD1306::begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  update();
}

void Display::update() 
{
  clearDisplay();
  setTextSize(1); 
  setTextColor(SSD1306_WHITE); 
  setCursor(0,0);       
  print(F("Speed: "));
  print((int) *vehicleSpeed);
  println(F(" km/h"));
  print(F("  RPM: "));
  println(*engineSpeed);
  display();
}