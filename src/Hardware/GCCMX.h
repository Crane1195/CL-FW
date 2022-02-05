#ifndef CLFW_GCCMX_H
#define CLFW_GCCMX_H

#include "../Classes/Pinout.h"

class CLFWController {
public:
    CLFWController() {
        original_Pinout.up           =  13;
        original_Pinout.down         =  14;
        original_Pinout.left         =  16;
        original_Pinout.right        =   3;
        original_Pinout.modX         =   2;
        original_Pinout.modY         =   0;
        original_Pinout.start        =   4;
        original_Pinout.select       =   1;
        original_Pinout.home         =  12;
        original_Pinout.a            =   9;
        original_Pinout.b            =  A2;
        original_Pinout.x            =  A1;
        original_Pinout.y            =  A5;
        original_Pinout.l1           = 255;
        original_Pinout.r1           =  A0; // GCC Z button
        original_Pinout.l2           =  15; // GCC L button
        original_Pinout.r2           =   7; // GCC R button
        original_Pinout.lightshield  =  A4;
        original_Pinout.midshield    =  A3;
        original_Pinout.cUp          =  10;
        original_Pinout.cDown        =   6;
        original_Pinout.cLeft        =   8;
        original_Pinout.cRight       =   5;

        multiplexer  = 11;
        consoleData  = 17;

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
