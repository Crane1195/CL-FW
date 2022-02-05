#ifndef CLFW_ARDUINODIY_H
#define CLFW_ARDUINODIY_H

#include "../Classes/Pinout.h"

class CLFWController {
public:
    CLFWController() {
        original_Pinout.up           =  13;
        original_Pinout.down         =   0;
        original_Pinout.left         =   1;
        original_Pinout.right        =   4;
        original_Pinout.modX         =   5;
        original_Pinout.modY         =   6;
        original_Pinout.start        =   7;
        original_Pinout.select       = 255;
        original_Pinout.home         = 255;
        original_Pinout.a            =  15;
        original_Pinout.b            =  A2;
        original_Pinout.x            =  A1;
        original_Pinout.y            =  A3;
        original_Pinout.l1           = 255;
        original_Pinout.r1           =  A0; // GCC Z button
        original_Pinout.l2           =  16; // GCC L button
        original_Pinout.r2           =  A4; // GCC R button
        original_Pinout.lightshield  =  11;
        original_Pinout.midshield    =  10;
        original_Pinout.cUp          =   8;
        original_Pinout.cDown        =  12;
        original_Pinout.cLeft        =   9;
        original_Pinout.cRight       =  14;

        multiplexer  = 255;
        consoleData  =  A5;

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
