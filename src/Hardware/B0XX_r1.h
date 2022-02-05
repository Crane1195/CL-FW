#ifndef CLFW_B0XX_R1_H
#define CLFW_B0XX_R1_H

#include "../Classes/Pinout.h"

class CLFWController {
public:
    CLFWController() {
        original_Pinout.up           =  A3;
        original_Pinout.down         =  16;
        original_Pinout.left         =  15;
        original_Pinout.right        =  14;
        original_Pinout.modX         =   6;
        original_Pinout.modY         =   8;
        original_Pinout.start        =  12;
        original_Pinout.select       = 255;
        original_Pinout.home         = 255;
        original_Pinout.a            =  13;
        original_Pinout.b            =   4;
        original_Pinout.x            =  A5;
        original_Pinout.y            =   1;
        original_Pinout.l1           = 255;
        original_Pinout.r1           =  A4; // GCC Z button
        original_Pinout.l2           =   7; // GCC L button
        original_Pinout.r2           =   0; // GCC R button
        original_Pinout.lightshield  = 255;
        original_Pinout.midshield    = 255;
        original_Pinout.cUp          =  A2;
        original_Pinout.cDown        =   5;
        original_Pinout.cLeft        =  A1;
        original_Pinout.cRight       =  A0;

        multiplexer  = 255;
        consoleData  =  17;

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
