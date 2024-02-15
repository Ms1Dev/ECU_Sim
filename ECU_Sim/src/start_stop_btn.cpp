#include <Arduino.h>
#include "start_stop_btn.h"


StartStopBtn::StartStopBtn(int pin)
{
    this->pin = pin;
}

void StartStopBtn::begin()
{
    pinMode(pin, INPUT);
}

bool StartStopBtn::update()
{
    if (!digitalRead(pin)) {
        btnHoldCounter++;
    }
    else {
        btnHoldCounter = 0;
    }

    return btnHoldCounter == btnHoldDuration;
}
