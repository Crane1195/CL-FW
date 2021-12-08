#ifndef CLFW_FGC_H
#define CLFW_FGC_H

#include "../Classes/ControllerStatus.h"
#include "../Classes/Modes.h"
#include "../Classes/Pinout.h"
#include "../Logic/DAC.h"

class FGCMode {

public:
    
    FGCMode(pinout original_Pinout, SOCD leftX, SOCD leftY, bool useUpPriority) {
        prioritizeUp = useUpPriority;
        current_Pinout = original_Pinout;

        current_Pinout.up     = original_Pinout.modX;
        // Second Up button
        current_Pinout.cUp    = original_Pinout.a;

        current_Pinout.down   = original_Pinout.down;
        current_Pinout.left   = original_Pinout.left;
        current_Pinout.right  = original_Pinout.right;
        current_Pinout.start  = original_Pinout.start;
        current_Pinout.select = original_Pinout.select;
        current_Pinout.home   = original_Pinout.home;
        current_Pinout.a      = original_Pinout.b;
        current_Pinout.b      = original_Pinout.x;
        current_Pinout.r2     = original_Pinout.r1;
        current_Pinout.l2     = original_Pinout.up;
        current_Pinout.x      = original_Pinout.r2;
        current_Pinout.y      = original_Pinout.y;
        current_Pinout.r1     = original_Pinout.lightshield;
        current_Pinout.l1     = original_Pinout.midshield;

        leftXSOCD = leftX;
        leftYSOCD = leftY;
    }

    outputStatus updateOutput(inputStatus *inputs) {
        
        // Incorporate second up button
        if (inputs->l_Up || inputs->r_Up)
            inputs->l_Up = true;

        digitalHandler(inputs, leftXSOCD, leftYSOCD, prioritizeUp);

        outputStatus outputs;

        outputs.a = inputs->a;
        outputs.b = inputs->b;
        outputs.x = inputs->x;
        outputs.y = inputs->y;

        outputs.start = inputs->start;
        outputs.select = inputs->select;
        outputs.home = inputs->home;

        if (inputs->modX && inputs->modY && inputs->home) {
            outputs.capture = true;
            outputs.home    = false;
        }
        else
            outputs.capture = false;

        if (inputs->modX && inputs->modY && inputs->select) {
            outputs.touchpad = true;
            outputs.select   = false;
        }
        else
            outputs.touchpad = false;

        // Unused
        outputs.leftStickX = 128;
        outputs.leftStickY = 128;
        outputs.rightStickX = 128;
        outputs.rightStickY = 128;
        outputs.triggerL = 0;
        outputs.triggerR = 0;

        outputs.r1 = inputs->r1;
        outputs.r2 = inputs->r2;
        outputs.l1 = inputs->l1;
        outputs.l2 = inputs->l2;

        outputs.dpadUp = inputs->l_Up;
        outputs.dpadDown = inputs->l_Down;
        outputs.dpadLeft = inputs->l_Left;
        outputs.dpadRight = inputs->l_Right;

        return outputs;
    }

    bool prioritizeUp;
    SOCD leftXSOCD, leftYSOCD, rightXSOCD, rightYSOCD;

    pinout current_Pinout;
};


#endif