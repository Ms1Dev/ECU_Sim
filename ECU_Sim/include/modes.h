#ifndef MODES_H
#define MODES_H

#include <stdint.h>


namespace modes {
    const unsigned char mode_0[] = {0x10, 0x0C, 0x0D, '\0'};
    const unsigned char mode_1[] = {0x11, 0x22, 0x11, 0x19, '\0'};
    const unsigned char mode_2[] = {0x11, 0x22, 0x11, 0x19, '\0'};
    const unsigned char mode_3[] = {0x11, 0x22, 0x11, 0x19, '\0'};

    struct OBD_Mode {
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
        {mode_3}
    };
}

#endif