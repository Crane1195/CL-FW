#ifndef CLFW_MODES_H
#define CLFW_MODES_H

#include "ControllerStatus.h"

enum device
{
    GC,
    N64,
    PC,
    NSW,
    KBD
};

enum game
{
    Melee,
    PM,
    Ultimate,
    RoA,
    NASB,
    FGC,
    DefaultKBD
};

enum SOCD {
    Neutral,
    TwoIP,
    TwoIPNoR,
    NormalKeyboard
};

device selectDevice(inputStatus buttonsPressed, bool hasUSB, int consoleData, bool USBDetected) {
    
    device returnDevice;

    //************************************************************************//
    // Device Selection 
    //       GC - Output as a controller via a GameCube cable for use on GC/Wii/GCC to USB adapters
    //      N64 - Output as a controller via an N64 cable for use on N64
    //       PC - Output as a controller via a USB cable for use on PC
    //      NSW - Output as a controller via a USB cable for use on Switch
    //      KBD - Output as a keyboard via a USB cable for use on PC
    
    // If a GC/N64 poll is detected
    if (!USBDetected) {
        // Use GC by default
        returnDevice = GC;

        // Use N64 if this button is pressed
        if (buttonsPressed.r_Up)
            returnDevice = N64;
    }
    // If a poll isn't detected, the controller is plugged in via USB
    else {
        // Make sure the board supports USB
        if (hasUSB) {
            // Use PC joystick mode by default
            returnDevice = PC;

            // Use keyboard mode if this button is pressed
            if (buttonsPressed.modY)
                returnDevice = KBD;
            
            // Use Switch joystick mode if this button is pressed
            else if (buttonsPressed.r_Left)
                returnDevice = NSW;

        }
    }

    return returnDevice;
}

game selectGame(inputStatus buttonsPressed, device activeDevice) {
    
    game returnGame;
    
    if (activeDevice != KBD) {
        // If nothing is pressed
        returnGame = Melee;

        if (buttonsPressed.b)
            returnGame = Ultimate;
        else if (buttonsPressed.x)
            returnGame = PM;
        else if (buttonsPressed.r1)
            returnGame = RoA;
        else if (buttonsPressed.l_Up)
            returnGame = FGC;
            
    }
    else {
        returnGame = DefaultKBD;
    }
    

    return returnGame;
}

#endif