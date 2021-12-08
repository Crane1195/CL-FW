#ifndef CLFW_KBD_H
#define CLFW_KBD_H

#include "../Classes/ControllerStatus.h"
#include "../Classes/Coordinates.h"
#include "../Classes/Modes.h"
#include "../Classes/Pinout.h"
#include "../Logic/DAC.h"

class KBDMode {
public:

    KBDMode(SOCD leftX, SOCD leftY, bool useUpPriority) {
        leftXSOCD = leftX;
        leftYSOCD = leftY;

        prioritizeUp = useUpPriority;

        current_Keymap.up          = 'a';
        current_Keymap.down        = 'b';
        current_Keymap.left        = 'c';
        current_Keymap.right       = 'd';
        current_Keymap.modX        = 'e';
        current_Keymap.modY        = 'f';
        current_Keymap.start       = 'g';
        current_Keymap.select      = 'h';
        current_Keymap.home        = 'i';
        current_Keymap.a           = 'j';
        current_Keymap.b           = 'k';
        current_Keymap.x           = 'l';
        current_Keymap.y           = 'm';
        current_Keymap.l1          = 'n';
        current_Keymap.r1          = 'o';
        current_Keymap.l2          = 'p';
        current_Keymap.r2          = 'q';
        current_Keymap.lightshield = 'r';
        current_Keymap.midshield   = 's';
        current_Keymap.cUp         = 't';
        current_Keymap.cDown       = 'u';
        current_Keymap.cLeft       = 'v';
        current_Keymap.cRight      = 'w';
    }

    void updateOutput(inputStatus *inputs) {
        digitalHandler(inputs, leftXSOCD, leftYSOCD, prioritizeUp);
    }

    bool prioritizeUp;

    pinout current_Keymap;
    SOCD leftXSOCD, leftYSOCD;
};

#endif