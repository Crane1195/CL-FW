#ifndef CLFW_HTANGL_V1_H
#define CLFW_HTANGL_V1_H

#include "../Classes/Pinout.h"

class CLFWController {
public:
    CLFWController() {
        original_Pinout.up           =  A0;
        original_Pinout.down         =   0;
        original_Pinout.left         =   4;
        original_Pinout.right        =   1;
        original_Pinout.modX         =  14;
        original_Pinout.modY         =  16;
        original_Pinout.start        =   3;
        original_Pinout.select       =   2;
        original_Pinout.home         =   5;
        original_Pinout.a            =  A5;
        original_Pinout.b            =   7;
        original_Pinout.x            =   9;
        original_Pinout.y            =  11;
        original_Pinout.l1           = 255;
        original_Pinout.r1           =  12; // GCC Z button
        original_Pinout.l2           =   6; // GCC L button
        original_Pinout.r2           =  10; // GCC R button
        original_Pinout.lightshield  =  13;
        original_Pinout.midshield    =  A1;
        original_Pinout.cUp          =  A3;
        original_Pinout.cDown        =  15;
        original_Pinout.cLeft        =  A2;
        original_Pinout.cRight       =  A4;

        multiplexer  = 255;
        consoleData  =   8;

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
