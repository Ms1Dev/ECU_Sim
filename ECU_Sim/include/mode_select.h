#ifndef MODE_SELECT_H
#define MODE_SELECT_H

#define NUM_SWITCHES 4

class Mode_select
{
private:
    class Switch
        {
        private:
            int pin;
        public:
            Switch(int pin);
            int getPinNum();
            bool readVal();
    };
    Switch switches[NUM_SWITCHES] = {
        Switch(4),
        Switch(5),
        Switch(6),
        Switch(7)
    };
    int mode = -1;
public:
    Mode_select();
    void begin();
    int getMode();
};

#endif