#ifndef CLFW_PM_H
#define CLFW_PM_H

#include "../Classes/ControllerStatus.h"
#include "../Classes/Coordinates.h"
#include "../Classes/Modes.h"
#include "../Classes/Pinout.h"
#include "../Logic/DAC.h"

class PMMode {

public:
    
    PMMode(pinout original_Pinout, SOCD leftX, SOCD leftY, SOCD rightX, SOCD rightY) {
        
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


        coords.maxOffset = 100;
        coords.neutral = 128;

        // Max Values                           X   Y
            coords.horizontal.set            (100,  0);
            coords.vertical.set              ( 0, 100);
            coords.diagonal.set               (70, 70);

        // Shield Drop
            coords.diagonal_Shield.set        (70, 70);
        
        // ModX
            // Tilts
            coords.modX_Horizontal.set        (70,  0);
            coords.modX_Vertical.set          ( 0, 60);

            // Side B Nerf
            coords.modX_Horizontal_B.set      (70,  0);
            coords.modX_Vertical_B.set        ( 0, 60);

            // Up B Angles
            coords.modX_Diagonal.set          (70, 34);
            coords.modX_Diagonal_cDown.set    (82, 32);
            coords.modX_Diagonal_cLeft.set    (84, 50);
            coords.modX_Diagonal_cUp.set      (77, 55);
            coords.modX_Diagonal_cRight.set   (72, 61);

            // Extended Up B Angles
            coords.modX_Diagonal_B.set        (89, 44);
            coords.modX_Diagonal_cDown_B.set  (92, 36);
            coords.modX_Diagonal_cLeft_B.set  (86, 51);
            coords.modX_Diagonal_cUp_B.set    (81, 58);
            coords.modX_Diagonal_cRight_B.set (76, 64);

            // Wavedash
            coords.modX_Diagonal_Shield.set   (68, 40);

            // Angled FSmash
            coords.modX_Angled_FSmash.set     (65, 23);
        
        // ModY
            // Tilts
            coords.modY_Horizontal.set        (28,  0);
            coords.modY_Vertical.set          ( 0, 34);

            // Side B Nerf
            coords.modY_Horizontal_B.set      (59,  0);
            coords.modY_Vertical_B.set        ( 0, 34);

            // Up B Angles
            coords.modY_Diagonal.set          (28, 58);
            coords.modY_Diagonal_cDown.set    (32, 82);
            coords.modY_Diagonal_cLeft.set    (50, 84);
            coords.modY_Diagonal_cUp.set      (55, 77);
            coords.modY_Diagonal_cRight.set   (61, 72);

            // Extended Up Y Angles
            coords.modY_Diagonal_B.set        (44, 89);
            coords.modY_Diagonal_cDown_B.set  (36, 92);
            coords.modY_Diagonal_cLeft_B.set  (51, 86);
            coords.modY_Diagonal_cUp_B.set    (58, 81);
            coords.modY_Diagonal_cRight_B.set (64, 76);

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
        
        return outputs;
    }

    coordinates coords;
    SOCD leftXSOCD, leftYSOCD, rightXSOCD, rightYSOCD;

    pinout current_Pinout;
};


#endif