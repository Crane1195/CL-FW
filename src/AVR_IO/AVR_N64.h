#ifndef CLFW_AVR_N64_H
#define CLFW_AVR_N64_H

#include <Nintendo.h>
#include "../Classes/ControllerStatus.h"

class N64Controller {
public:

    N64Controller() {

    }

    void initialize(int dataLine, bool useSendDelay) {
        useDelay = useSendDelay;
        sendDelay = 0;

        N64Console = new CN64Console(dataLine);
        d = defaultN64Data;
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
        d.report.start  = outputs.start;
        
        d.report.a      = outputs.a;
        d.report.b      = outputs.b;

        d.report.z      = outputs.r1;
        d.report.r      = outputs.r2;
        d.report.l      = outputs.l2;

        d.report.dup    = outputs.dpadUp;
        d.report.ddown  = outputs.dpadDown;
        d.report.dleft  = outputs.dpadLeft;
        d.report.dright = outputs.dpadRight;

        d.report.xAxis  = outputs.leftStickX - 128;
        d.report.yAxis  = outputs.leftStickY - 128;
        
        d.report.cup    = outputs.rightStickY > 128;
        d.report.cdown  = outputs.rightStickY < 128;
        d.report.cleft  = outputs.rightStickX < 128;
        d.report.cright = outputs.rightStickX > 128;

        N64Console->write(d);

        if (useDelay)
            delayMicroseconds(sendDelay);
    }

private:
    CN64Console *N64Console;
    N64_Data_t d;

    bool useDelay;
    int sendDelay;
};

#endif