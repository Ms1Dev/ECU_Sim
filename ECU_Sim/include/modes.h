#ifndef MODES_H
#define MODES_H

#include <stdint.h>


namespace modes {
    const unsigned char mode_0[] = {'\0'}; // no parameters
    const unsigned char mode_1[] = {0x20, 0x40, 0x60, 0x0C, 0x0D, 0x10, 0x11, '\0'}; // standard MAF
    const unsigned char mode_2[] = {0x20, 0x40, 0x60, 0x0C, 0x0D, 0x66, 0x11, '\0'}; // alternative MAF
    const unsigned char mode_3[] = {0x20, 0x40, 0x60, 0x0C, 0x0D, 0x0F, 0x0B, 0x11, '\0'}; // manifold pressure and temperature no MAF
    const unsigned char mode_4[] = {
                                    0x20, 0x40, 0x01, 0x03, 0x04, 0x05, 0x06, 0x07, 0x0B, 0x0C, 
                                    0x0D, 0x0E, 0x0F, 0x11, 0x13, 0x14, 0x15, 0x1C, 0x21, 0x2E, 
                                    0x2F, 0x33, 0x42, 0x44, '\0'
                                    }; // ford focus petrol 1.6 2008 
    const unsigned char mode_5[] = {0x20, 0x40, 0x60, 0x0D, 0x10, 0x11, '\0'}; // no rpm
    const unsigned char mode_6[] = {0x20, 0x40, 0x60, 0x0C, 0x10, 0x11, '\0'}; // no speed
    const unsigned char mode_7[] = {0x20, 0x40, 0x60, 0x10, 0x11, '\0'}; // no speed or rpm
    const unsigned char mode_8[] = {0x20, 0x40, 0x60, 0x0C, 0x0D, 0x11, '\0'}; // no MAF or MAP
    const unsigned char mode_9[] = {0x20, 0x40, 0x60, 0x0C, 0x0D, 0x10, 0x11, 0x51, '\0'}; // standard MAF with fuel type

    struct OBD_Mode {
        static const int default_mode = 1;
        const unsigned char *supportedPids;
        uint8_t pidCount;
        OBD_Mode(const unsigned char* supportedPids) : supportedPids(supportedPids) {
            pidCount = 0;
            while (supportedPids[pidCount] != '\0') {
                pidCount++;
            }
        }
    };

    const OBD_Mode obd_modes[]{
        {mode_0},
        {mode_1},
        {mode_2},
        {mode_3},
        {mode_4},
        {mode_5},
        {mode_6},
        {mode_7},
        {mode_8},
        {mode_9}
    };

    const int mode_count = sizeof(obd_modes) / sizeof(OBD_Mode);
}

#endif