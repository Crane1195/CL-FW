#ifndef CLFW_GGS_H
#define CLFW_GGS_H

#include "../Classes/ControllerStatus.h"
#include "../Classes/Coordinates.h"
#include "../Classes/Modes.h"
#include "../Classes/Pinout.h"
#include "../Logic/DAC.h"

class GGSMode {
public:

    GGSMode(SOCD leftX, SOCD leftY, bool useUpPriority) {
        leftXSOCD = leftX;
        leftYSOCD = leftY;

        prioritizeUp = useUpPriority;

        current_Keymap.up          = 'w';
        current_Keymap.down        = 's';
        current_Keymap.left        = 'a';
        current_Keymap.right       = 'd';
        current_Keymap.modX        = 'w';
        current_Keymap.modY        = 'f';
        current_Keymap.start       = 'e';
        current_Keymap.select      = 'h';
        current_Keymap.home        = 'i';
        current_Keymap.a           = 'u';
        current_Keymap.b           = 'j';
        current_Keymap.x           = 'o';
        current_Keymap.y           = 'i';
        current_Keymap.l1          = 'n';
        current_Keymap.r1          = 'u';
        current_Keymap.l2          = 'k';
        current_Keymap.r2          = 'q';
        current_Keymap.lightshield = 'q';
        current_Keymap.midshield   = 's';
        current_Keymap.cUp         = 't';
        current_Keymap.cDown       = 'l';
        current_Keymap.cLeft       = 'v';
        current_Keymap.cRight      = 'b';
    }

    void updateOutput(inputStatus *inputs) {
        digitalHandler(inputs, leftXSOCD, leftYSOCD, prioritizeUp);
    }

    bool prioritizeUp;

    pinout current_Keymap;
    SOCD leftXSOCD, leftYSOCD;
};

#endif