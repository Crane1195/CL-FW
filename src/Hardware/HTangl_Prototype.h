#ifndef CLFW_HTANGL_PROTOTYPE_H
#define CLFW_HTANGL_PROTOTYPE_H

#include "../Classes/Pinout.h"

class CLFWController {
public:
    CLFWController() {
        original_Pinout.up           =   4;
        original_Pinout.down         =  A3;
        original_Pinout.left         =  A4;
        original_Pinout.right        =  15;
        original_Pinout.modX         =  16;
        original_Pinout.modY         =  14;
        original_Pinout.start        =   1;
        original_Pinout.select       =   0;
        original_Pinout.home         =   2;
        original_Pinout.a            =   9;
        original_Pinout.b            =  A1;
        original_Pinout.x            =  A2;
        original_Pinout.y            =   5;
        original_Pinout.l1           = 255;
        original_Pinout.r1           =   3; // GCC Z button
        original_Pinout.l2           =  A5; // GCC L button
        original_Pinout.r2           =   6; // GCC R button
        original_Pinout.lightshield  =  13;
        original_Pinout.midshield    =  12;
        original_Pinout.cUp          =  11;
        original_Pinout.cDown        =   7;
        original_Pinout.cLeft        =   8;
        original_Pinout.cRight       =  10;

        multiplexer  = 255;
        consoleData  =  A0;

        current_Pinout   = original_Pinout;

        defaultMUX = false;

        #if defined(HAS_USB)
            hasUSB = true;
        #else
            hasUSB = false;
        #endif
    }

    pinout current_Pinout;
    pinout original_Pinout;

    int multiplexer;
    int consoleData;

    pinout current_Keymap;

    bool defaultMUX;
    bool hasUSB;
};

#endif
