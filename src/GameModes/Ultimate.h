#ifndef CLFW_ULTIMATE_H
#define CLFW_ULTIMATE_H

#include "../Classes/ControllerStatus.h"
#include "../Classes/Coordinates.h"
#include "../Classes/Modes.h"
#include "../Classes/Pinout.h"
#include "../Logic/DAC.h"

class ultimateMode {

public:
    
    ultimateMode(pinout original_Pinout, SOCD leftX, SOCD leftY, SOCD rightX, SOCD rightY) {
        
        current_Pinout = original_Pinout;

        // If you want to change this modes default mapping, you can do so here.
        // current_Pinout.up           = original_Pinout.up         ;
        // current_Pinout.down         = original_Pinout.down       ;
        // current_Pinout.left         = original_Pinout.left       ;
        // current_Pinout.right        = original_Pinout.right      ;
        // current_Pinout.modX         = original_Pinout.modX       ;
        // current_Pinout.modY         = original_Pinout.modY       ;
        // current_Pinout.start        = original_Pinout.start      ;
        // current_Pinout.select       = original_Pinout.select     ;
        // current_Pinout.home         = original_Pinout.home       ;
        // current_Pinout.a            = original_Pinout.a          ;
        // current_Pinout.b            = original_Pinout.b          ;
        // current_Pinout.x            = original_Pinout.x          ;
        // current_Pinout.y            = original_Pinout.y          ;
        // current_Pinout.l1           = original_Pinout.l1         ;
        // current_Pinout.r1           = original_Pinout.r1         ;
        // current_Pinout.l2           = original_Pinout.l2         ;
        // current_Pinout.r2           = original_Pinout.r2         ;
        // current_Pinout.lightshield  = original_Pinout.lightshield;
        // current_Pinout.midshield    = original_Pinout.midshield  ;
        // current_Pinout.cUp          = original_Pinout.cUp        ;
        // current_Pinout.cDown        = original_Pinout.cDown      ;
        // current_Pinout.cLeft        = original_Pinout.cLeft      ;
        // current_Pinout.cRight       = original_Pinout.cRight     ;


        coords.maxOffset = 80;
        coords.neutral = 128;

        // Max Value                            X   Y
            coords.diagonal.set               (56, 56);

        // Shield Drop
            coords.diagonal_Shield.set        (56, 56);
        
        // ModX
            // Tilts
            coords.modX_Horizontal.set        (40,  0);
            coords.modX_Vertical.set          ( 0, 49);

            // Side B Nerf
            coords.modX_Horizontal_B.set      (47,  0);
            coords.modX_Vertical_B.set        ( 0, 41);

            // Up B Angles
            coords.modX_Diagonal.set          (40, 26);
            coords.modX_Diagonal_cDown.set    (61, 49);
            coords.modX_Diagonal_cLeft.set    (66, 42);
            coords.modX_Diagonal_cUp.set      (71, 35);
            coords.modX_Diagonal_cRight.set   (75, 27);

            // Extended Up B Angles
            coords.modX_Diagonal_B.set        (75, 27);
            coords.modX_Diagonal_cDown_B.set  (61, 49);
            coords.modX_Diagonal_cLeft_B.set  (66, 42);
            coords.modX_Diagonal_cUp_B.set    (71, 35);
            coords.modX_Diagonal_cRight_B.set (75, 27);

            // Wavedash
            coords.modX_Diagonal_Shield.set   (51, 30);

            // Angled FSmash
            coords.modX_Angled_FSmash.set     (65, 23);
        
        // ModY
            // Tilts
            coords.modY_Horizontal.set        (27,  0);
            coords.modY_Vertical.set          ( 0, 51);

            // Side B Nerf
            coords.modY_Horizontal_B.set      (53,  0);
            coords.modY_Vertical_B.set        ( 0, 61);

            // Up B Angles
            coords.modY_Diagonal.set          (38, 49);
            coords.modY_Diagonal_cDown.set    (49, 61);
            coords.modY_Diagonal_cLeft.set    (42, 66);
            coords.modY_Diagonal_cUp.set      (35, 71);
            coords.modY_Diagonal_cRight.set   (27, 75);

            // Extended Up Y Angles
            coords.modY_Diagonal_B.set        (38, 49);
            coords.modY_Diagonal_cDown_B.set  (49, 61);
            coords.modY_Diagonal_cLeft_B.set  (42, 66);
            coords.modY_Diagonal_cUp_B.set    (35, 71);
            coords.modY_Diagonal_cRight_B.set (27, 75);

            // Wavedash
            coords.modY_Diagonal_Shield.set   (40, 68);

            leftXSOCD = leftX;
            leftYSOCD = leftY;
            rightXSOCD = rightX;
            rightYSOCD = rightY;

    }

    outputStatus updateOutput(inputStatus *inputs) {
        outputStatus outputs = rectangleDAC(inputs, coords, leftXSOCD, leftYSOCD, rightXSOCD, rightYSOCD);
        
        outputs.a = inputs->a;
        outputs.b = inputs->b;
        outputs.x = inputs->x;
        outputs.y = inputs->y;

        outputs.start = inputs->start;
        outputs.select = inputs->select;
        outputs.home = inputs->home;

        outputs.capture = (inputs->modX && inputs->modY && inputs->home);
        
        // Unused
        outputs.touchpad = false;

        // Shoulders
        outputs.r1 = inputs->r1;
        outputs.l1 = inputs->l1;

        // Triggers
        outputs.r2 = inputs->r2;
        outputs.l2 = inputs->l2;

        if (inputs->r2)
            outputs.triggerR = 140;
        else
            outputs.triggerR = 0;
        
        if (inputs->l2)
            outputs.triggerL = 140;
        else 
            outputs.triggerL = 0;

        // Dpad is modX + modY + C stick
        outputs.dpadUp = (inputs->modX && inputs->modY && inputs->r_Up);
        outputs.dpadDown = (inputs->modX && inputs->modY && inputs->r_Down);
        // If you have select/home buttons, those can be used too
        outputs.dpadLeft = ((inputs->modX && inputs->modY && inputs->r_Left) || inputs->select);
        outputs.dpadRight = ((inputs->modX && inputs->modY && inputs->r_Right) || inputs->home);

        return outputs;
    }

    coordinates coords;
    SOCD leftXSOCD, leftYSOCD, rightXSOCD, rightYSOCD;

    pinout current_Pinout;
};


#endif