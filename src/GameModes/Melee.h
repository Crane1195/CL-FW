#ifndef CLFW_MELEE_H
#define CLFW_MELEE_H

#include "../Classes/ControllerStatus.h"
#include "../Classes/Coordinates.h"
#include "../Classes/Modes.h"
#include "../Classes/Pinout.h"
#include "../Logic/DAC.h"

class meleeMode {

public:
    
    meleeMode(pinout original_Pinout, SOCD leftX, SOCD leftY, SOCD rightX, SOCD rightY) {
        
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

        // Max Values                           X   Y
            coords.horizontal.set             (80,  0);
            coords.vertical.set               ( 0, 80);
            coords.diagonal.set               (56, 56);

        // Shield Drop
            coords.diagonal_Shield.set        (56, 55);
        
        // ModX
            // Tilts
            coords.modX_Horizontal.set        (53,  0);
            coords.modX_Vertical.set          ( 0, 43);

            // Side B Nerf
            coords.modX_Horizontal_B.set      (53,  0);
            coords.modX_Vertical_B.set        ( 0, 43);

            // Up B Angles
            coords.modX_Diagonal.set          (59, 25);
            coords.modX_Diagonal_cDown.set    (56, 29);
            coords.modX_Diagonal_cLeft.set    (63, 39);
            coords.modX_Diagonal_cUp.set      (56, 41);
            coords.modX_Diagonal_cRight.set   (49, 42);

            // Extended Up B Angles
            coords.modX_Diagonal_B.set        (73, 31);
            coords.modX_Diagonal_cDown_B.set  (70, 36);
            coords.modX_Diagonal_cLeft_B.set  (68, 42);
            coords.modX_Diagonal_cUp_B.set    (59, 43);
            coords.modX_Diagonal_cRight_B.set (51, 43);

            // Wavedash
            coords.modX_Diagonal_Shield.set   (51, 30);

            // Angled FSmash
            coords.modX_Angled_FSmash.set     (68, 42);
        
        // ModY
            // Tilts
            coords.modY_Horizontal.set        (27,  0);
            coords.modY_Vertical.set          ( 0, 59);

            // Side B Nerf
            coords.modY_Horizontal_B.set      (53,  0);
            coords.modY_Vertical_B.set        ( 0, 59);

            // Up B Angles
            coords.modY_Diagonal.set          (25, 59);
            coords.modY_Diagonal_cDown.set    (29, 56);
            coords.modY_Diagonal_cLeft.set    (39, 63);
            coords.modY_Diagonal_cUp.set      (41, 56);
            coords.modY_Diagonal_cRight.set   (51, 61);

            // Extended Up Y Angles
            coords.modY_Diagonal_B.set        (31, 73);
            coords.modY_Diagonal_cDown_B.set  (36, 70);
            coords.modY_Diagonal_cLeft_B.set  (42, 68);
            coords.modY_Diagonal_cUp_B.set    (47, 64);
            coords.modY_Diagonal_cRight_B.set (47, 57);

            // Wavedash
            coords.modY_Diagonal_Shield.set   (40, 68);

            leftXSOCD = leftX;
            leftYSOCD = leftY;
            rightXSOCD = rightX;
            rightYSOCD = rightY;

    }

    outputStatus updateOutput(inputStatus *inputs) {
        outputStatus outputs = rectangleDAC(inputs, coords, leftXSOCD, leftYSOCD, rightXSOCD, rightYSOCD);
        
        if (inputs->l_Left && inputs->l_Right && (outputs.leftStickX != coords.neutral) && !inputs->r2 && !inputs->l2 && !inputs->lightshield && !inputs->midshield) {
            if (outputs.leftStickX > coords.neutral)
                outputs.leftStickX = coords.neutral + coords.maxOffset;
            else
                outputs.leftStickX = coords.neutral - coords.maxOffset;
        }

        outputs.a = inputs->a;
        outputs.b = inputs->b;
        outputs.x = inputs->x;
        outputs.y = inputs->y;

        outputs.start = inputs->start;
        
        // Unused
        outputs.l1 = false;
        outputs.select = false;
        outputs.home = false;
        outputs.capture = false;
        outputs.touchpad = false;

        // Melee Z button
        outputs.r1 = inputs->r1;

        // Melee triggers
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
        // If you have select/home buttons, those can be used too for faster save/load state
        outputs.dpadLeft = ((inputs->modX && inputs->modY && inputs->r_Left) || inputs->select);
        outputs.dpadRight = ((inputs->modX && inputs->modY && inputs->r_Right) || inputs->home);

        if (inputs->midshield)
            outputs.triggerR = 95;
        if (inputs->lightshield)
            outputs.triggerR = 50;

        return outputs;
    }

    coordinates coords;
    SOCD leftXSOCD, leftYSOCD, rightXSOCD, rightYSOCD;

    pinout current_Pinout;
};


#endif