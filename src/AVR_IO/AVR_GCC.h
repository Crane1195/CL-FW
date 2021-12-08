#ifndef CLFW_AVR_GCC_H
#define CLFW_AVR_GCC_H

#include <Nintendo.h>
#include "../Classes/ControllerStatus.h"

class GCController {
public:

    GCController() {

    }

    void initialize(int dataLine, bool useSendDelay) {
        useDelay = useSendDelay;
        sendDelay = 0;

        GameCubeConsole = new CGamecubeConsole(dataLine);
        d = defaultGamecubeData;
    }
    
    void setDelay(int pollingRate) {
        float tempVal;

        tempVal = 1 / pollingRate; // Convert from Hz to seconds
        tempVal *= 1000000;        // Convert from seconds to microseconds
        tempVal -= 2500;           // Remove time to account for MCU speed

        // Confirm the value does not go below 0
        if (tempVal < 0)
            tempVal = 0;
        
        sendDelay = tempVal;
    }

    void sendOutput (outputStatus outputs) {
        d.report.l      = outputs.l2;
        d.report.start  = outputs.start;
        d.report.b      = outputs.b;
        d.report.x      = outputs.x;
        d.report.z      = outputs.r1;
        d.report.r      = outputs.r2;
        d.report.y      = outputs.y;
        d.report.a      = outputs.a;
        d.report.dup    = outputs.dpadUp;
        d.report.ddown  = outputs.dpadDown;
        d.report.dleft  = outputs.dpadLeft;
        d.report.dright = outputs.dpadRight;

        d.report.xAxis  = outputs.leftStickX;
        d.report.yAxis  = outputs.leftStickY;
        d.report.cxAxis = outputs.rightStickX;
        d.report.cyAxis = outputs.rightStickY;
        d.report.right  = outputs.triggerR + 30;
        d.report.left   = outputs.triggerL + 30;

        GameCubeConsole->write(d);

        if (useDelay)
            delayMicroseconds(sendDelay);
    }

private:
    CGamecubeConsole *GameCubeConsole;
    Gamecube_Data_t d;
    
    bool useDelay;
    int sendDelay;
};

#endif