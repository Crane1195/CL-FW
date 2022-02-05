#ifndef CLFW_SMASHBOX_H
#define CLFW_SMASHBOX_H

#include "../Classes/Pinout.h"

class CLFWController {
public:
    CLFWController() {
        original_Pinout.up           =  45;
        original_Pinout.down         =  23;
        original_Pinout.left         =  24;
        original_Pinout.right        =  25;
        original_Pinout.modX         =  28;
        original_Pinout.modY         =  29;
        original_Pinout.start        =  50;
        original_Pinout.select       = 255;
        original_Pinout.home         = 255;
        original_Pinout.a            =  35;
        original_Pinout.b            =  44;
        original_Pinout.x            =  42;
        original_Pinout.y            =  43;
        original_Pinout.l1           = 255;
        original_Pinout.r1           =   7; // GCC Z button
        original_Pinout.l2           =  47; // GCC L button
        original_Pinout.r2           =  41; // GCC R button
        original_Pinout.lightshield  =  40;
        original_Pinout.midshield    =  12;
        original_Pinout.cUp          =  34;
        original_Pinout.cDown        =  46;
        original_Pinout.cLeft        =  36;
        original_Pinout.cRight       =  37;

        multiplexer  = 255;
        consoleData  =  52;

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
