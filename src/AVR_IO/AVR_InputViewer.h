#ifndef CLFW_AVR_INPUTVIEWER_H
#define CLFW_AVR_INPUTVIEWER_H

#include "../Classes/ControllerStatus.h"

void sendIVData(inputStatus inputs, int *IVCounter) {

    if (Serial.availableForWrite() > 32) {
        if (*IVCounter == 0) {
            byte report[25] = {
                // 0x31 = Pressed
                // 0x40 = Not Pressed
                // 0x0A = End transfer
                inputs.start        ? 0x31 : 0x30,
                inputs.y            ? 0x31 : 0x30,
                inputs.x            ? 0x31 : 0x30,
                inputs.b            ? 0x31 : 0x30,
                inputs.a            ? 0x31 : 0x30,
                inputs.l2           ? 0x31 : 0x30,
                inputs.r2           ? 0x31 : 0x30,
                inputs.r1           ? 0x31 : 0x30,
                inputs.l_Up         ? 0x31 : 0x30,
                inputs.l_Down       ? 0x31 : 0x30,
                inputs.l_Right      ? 0x31 : 0x30,
                inputs.l_Left       ? 0x31 : 0x30,
                inputs.modX         ? 0x31 : 0x30,
                inputs.modY         ? 0x31 : 0x30,
                inputs.r_Left       ? 0x31 : 0x30,
                inputs.r_Right      ? 0x31 : 0x30,
                inputs.r_Up         ? 0x31 : 0x30,
                inputs.r_Down       ? 0x31 : 0x30,
                inputs.lightshield  ? 0x31 : 0x30,
                inputs.midshield    ? 0x31 : 0x30,
                                             0x30, // These might be needed for some reason
                                             0x30,
                                             0x30,
                                             0x30,
                0x0A
            };

            Serial.write(report, 25);
        }
        else if (*IVCounter == 3) {
            *IVCounter = 0;
        }
        else
            *IVCounter++;
    }
}

#endif