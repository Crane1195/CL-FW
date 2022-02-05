#ifndef CLFW_MODEL_S_2_H
#define CLFW_MODEL_S_2_H

#include "../Classes/Pinout.h"

class CLFWController {
public:
    CLFWController() {
        original_Pinout.up           =  15;
        original_Pinout.down         =  13;
        original_Pinout.left         =  10;
        original_Pinout.right        =   5;
        original_Pinout.modX         =   7;
        original_Pinout.modY         =   3;
        original_Pinout.start        =   6;
        original_Pinout.select       =   9;
        original_Pinout.home         =   8;
        original_Pinout.a            =  A2;
        original_Pinout.b            =  A5;
        original_Pinout.x            =  14;
        original_Pinout.y            =   4;
        original_Pinout.l1           = 255;
        original_Pinout.r1           =  16; // GCC Z button
        original_Pinout.l2           =   2; // GCC L button
        original_Pinout.r2           =  12; // GCC R button
        original_Pinout.lightshield  =   1;
        original_Pinout.midshield    =   0;
        original_Pinout.cUp          =  A3;
        original_Pinout.cDown        =  A0;
        original_Pinout.cLeft        =  A1;
        original_Pinout.cRight       =  A4;
 
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
