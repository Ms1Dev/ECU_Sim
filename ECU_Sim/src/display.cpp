#include "display.h"


Display::Display() :
Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET)
{  
}

Display::~Display()
{
}

void Display::begin() 
{
  Adafruit_SSD1306::begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);

  display();
  delay(2000); 
  clearDisplay();

  setTextSize(1); 
  setTextColor(SSD1306_WHITE); 
  setCursor(0,0);       
  println(F("Hello, world!"));

  display();
  delay(2000);
}