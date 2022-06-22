#ifndef CLFW_LBX_H
#define CLFW_LBX_H

#include "../Classes/Pinout.h"

class CLFWController {
public:
    CLFWController() {
        original_Pinout.up           =   9;
        original_Pinout.down         =  16;
        original_Pinout.left         =  15;
        original_Pinout.right        =  14;
        original_Pinout.modX         =   3;
        original_Pinout.modY         =   0;
        original_Pinout.start        =  A5;
        original_Pinout.select       = 255;
        original_Pinout.home         = 255;
        original_Pinout.a            =  12;
        original_Pinout.b            =  13;
        original_Pinout.x            =   5;
        original_Pinout.y            =  A1;
        original_Pinout.l1           = 255;
        original_Pinout.r1           =  10; // GCC Z button
        original_Pinout.l2           =  11; // GCC L button
        original_Pinout.r2           =  A0; // GCC R button
        original_Pinout.lightshield  =  A2;
        original_Pinout.midshield    =  A3;
        original_Pinout.cUp          =   8;
        original_Pinout.cDown        =   1;
        original_Pinout.cLeft        =   4;
        original_Pinout.cRight       =   6;

        multiplexer  = A4;
        consoleData  =  7;

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
