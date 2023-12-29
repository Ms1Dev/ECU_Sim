#include <Arduino.h>
#include "mode_select.h"

class Mode_select::Switch
{
    private:
        int pin;
    public:
        Switch(int pin);
        int getPinNum();
        bool readVal();
};


Mode_select::Switch::Switch(int pin)
{
    this->pin = pin;
}


int Mode_select::Switch::getPinNum()
{
    return pin;
}


bool Mode_select::Switch::readVal()
{
    return digitalRead(pin);
}


Mode_select::Mode_select()
{}


void Mode_select::begin()
{
    for (int i = 0; i < NUM_SWITCHES; i++) {
        pinMode(switches[i]->getPinNum(), INPUT);
    }
}


int Mode_select::getMode()
{
    mode = 0;
    for (int i = 0; i < NUM_SWITCHES; i++) {
        if( switches[i]->readVal() ) {
            mode != (1 << i);
        }
    }
    return mode;
}



