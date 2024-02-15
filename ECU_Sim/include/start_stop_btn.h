#ifndef START_STOP_BTN_H
#define START_STOP_BTN_Hv


class StartStopBtn
{
private:
    const int btnHoldDuration = 15000;
    int btnHoldCounter = 0;
    int pin;
public:
    StartStopBtn(int pin);
    void begin();
    bool update();
};

#endif