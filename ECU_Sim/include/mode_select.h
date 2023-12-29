#ifndef MODE_SELECT_H
#define MODE_SELECT_H

#define NUM_SWITCHES 4

class Mode_select
{
private:
    class Switch;
    Switch *switches[NUM_SWITCHES];
    int mode = -1;
public:
    Mode_select();
    void begin();
    int getMode();
};

#endif