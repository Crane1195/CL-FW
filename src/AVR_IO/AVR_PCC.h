#ifndef CLFW_AVR_PCC_H
#define CLFW_AVR_PCC_H

#include <Joystick.h>
#include "./AVR_InputViewer.h"
#include "../Classes/ControllerStatus.h"

class PCController {
public:

    PCController() {
        initFlag = false;
    }

    void initialize() {

        initFlag = true;

        JoystickPC = new Joystick_(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
            13, 1,                 // Button Count, Hat Switch Count
            true, true, false,     // X and Y, but no Z Axis
            true, true, false,     // Rx, Ry, no Rz
            true, true,            // Rudder, throttle
            false, false, false    // No accelerator, no brake, no steering
        );

        JoystickPC->begin(false);
        JoystickPC->setXAxisRange(0, 255);
        JoystickPC->setYAxisRange(0, 255);
        JoystickPC->setZAxisRange(0, 255);
        JoystickPC->setRxAxisRange(0, 255);
        JoystickPC->setRyAxisRange(0, 255);
        JoystickPC->setThrottleRange(0, 255);  

        IVCounter = 0;
        Serial.begin(115200, SERIAL_8N1);
    }

    void sendOutput (inputStatus inputs, outputStatus outputs) {

        JoystickPC->setButton(0, outputs.a);
        JoystickPC->setButton(1, outputs.b);
        JoystickPC->setButton(2, outputs.x);
        JoystickPC->setButton(3, outputs.y);
        JoystickPC->setButton(4, outputs.r1);
        JoystickPC->setButton(5, outputs.l1);
        JoystickPC->setButton(6, outputs.r2);
        JoystickPC->setButton(7, outputs.l2);
        JoystickPC->setButton(8, outputs.start);
        JoystickPC->setButton(9, outputs.select);
        JoystickPC->setButton(10, outputs.home);
        JoystickPC->setButton(11, outputs.capture);
        JoystickPC->setButton(12, outputs.touchpad);
        JoystickPC->setXAxis(outputs.leftStickX);
        JoystickPC->setYAxis(255 - outputs.leftStickY);
        JoystickPC->setRxAxis(outputs.rightStickX);
        JoystickPC->setRyAxis(255 - outputs.rightStickY);
        JoystickPC->setThrottle(outputs.triggerR);
        JoystickPC->setRudder(outputs.triggerL);

        JoystickPC->setHatSwitch(0, getHatValue(outputs));
        
        JoystickPC->sendState();

        sendIVData(inputs, &IVCounter);

    }

    int getHatValue(outputStatus outputs) {
        int positionX = 0;
        int positionY = 0;
        int hatval = -1;

        if      (outputs.dpadLeft)  positionX = -1;
        else if (outputs.dpadRight) positionX =  1;
        else                        positionX =  0;

        if      (outputs.dpadDown)  positionY = -1;
        else if (outputs.dpadUp)    positionY =  1;
        else                        positionY =  0;

        if (positionX != 0 && positionY == 0) hatval = 180 - (positionX * 90);
        if (positionX == 0 && positionY != 0) hatval =  90 - (positionY * 90);
        if (positionX != 0 && positionY != 0) {
            hatval = 180 - (positionX * 90);
            hatval = hatval - (positionX * positionY * 45);
        }
        return hatval;
    }

    bool initFlag;
    Joystick_ *JoystickPC;
    int IVCounter;
};

#endif