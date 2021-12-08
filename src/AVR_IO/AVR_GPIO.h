#ifndef CLFW_AVR_GPIO_H
#define CLFW_AVR_GPIO_H

#include "../Classes/Pinout.h"
#include "../Classes/ControllerStatus.h"

void initializeButtons (pinout inputs) {
    if (inputs.up          != 255)    pinMode(inputs.up,          INPUT_PULLUP);
    if (inputs.down        != 255)    pinMode(inputs.down,        INPUT_PULLUP);
    if (inputs.left        != 255)    pinMode(inputs.left,        INPUT_PULLUP);
    if (inputs.right       != 255)    pinMode(inputs.right,       INPUT_PULLUP);
    if (inputs.cUp         != 255)    pinMode(inputs.cUp,         INPUT_PULLUP);
    if (inputs.cDown       != 255)    pinMode(inputs.cDown,       INPUT_PULLUP);
    if (inputs.cLeft       != 255)    pinMode(inputs.cLeft,       INPUT_PULLUP);
    if (inputs.cRight      != 255)    pinMode(inputs.cRight,      INPUT_PULLUP);
    if (inputs.modX        != 255)    pinMode(inputs.modX,        INPUT_PULLUP);
    if (inputs.modY        != 255)    pinMode(inputs.modY,        INPUT_PULLUP);
    if (inputs.start       != 255)    pinMode(inputs.start,       INPUT_PULLUP);
    if (inputs.select      != 255)    pinMode(inputs.select,      INPUT_PULLUP);
    if (inputs.home        != 255)    pinMode(inputs.home,        INPUT_PULLUP);
    if (inputs.a           != 255)    pinMode(inputs.a,           INPUT_PULLUP);
    if (inputs.b           != 255)    pinMode(inputs.b,           INPUT_PULLUP);
    if (inputs.x           != 255)    pinMode(inputs.x,           INPUT_PULLUP);
    if (inputs.y           != 255)    pinMode(inputs.y,           INPUT_PULLUP);
    if (inputs.l1          != 255)    pinMode(inputs.l1,          INPUT_PULLUP);
    if (inputs.r1          != 255)    pinMode(inputs.r1,          INPUT_PULLUP);
    if (inputs.l2          != 255)    pinMode(inputs.l2,          INPUT_PULLUP);
    if (inputs.r2          != 255)    pinMode(inputs.r2,          INPUT_PULLUP);
    if (inputs.lightshield != 255)    pinMode(inputs.lightshield, INPUT_PULLUP);
    if (inputs.midshield   != 255)    pinMode(inputs.midshield,   INPUT_PULLUP);
}

void readAllButtons(inputStatus *currentStatus, pinout inputs) {

    // If the button is present... set the button's status....... to be pressed when the pin is low.
    if (inputs.up          != 255) currentStatus->l_Up        = (digitalRead(inputs.up)          == LOW);       
    if (inputs.down        != 255) currentStatus->l_Down      = (digitalRead(inputs.down)        == LOW);
    if (inputs.left        != 255) currentStatus->l_Left      = (digitalRead(inputs.left)        == LOW);
    if (inputs.right       != 255) currentStatus->l_Right     = (digitalRead(inputs.right)       == LOW);
    if (inputs.cUp         != 255) currentStatus->r_Up        = (digitalRead(inputs.cUp)         == LOW);
    if (inputs.cDown       != 255) currentStatus->r_Down      = (digitalRead(inputs.cDown)       == LOW);
    if (inputs.cLeft       != 255) currentStatus->r_Left      = (digitalRead(inputs.cLeft)       == LOW);
    if (inputs.cRight      != 255) currentStatus->r_Right     = (digitalRead(inputs.cRight)      == LOW);
    if (inputs.modX        != 255) currentStatus->modX        = (digitalRead(inputs.modX)        == LOW);
    if (inputs.modY        != 255) currentStatus->modY        = (digitalRead(inputs.modY)        == LOW);
    if (inputs.start       != 255) currentStatus->start       = (digitalRead(inputs.start)       == LOW);
    if (inputs.select      != 255) currentStatus->select      = (digitalRead(inputs.select)      == LOW);
    if (inputs.home        != 255) currentStatus->home        = (digitalRead(inputs.home)        == LOW);
    if (inputs.a           != 255) currentStatus->a           = (digitalRead(inputs.a)           == LOW);
    if (inputs.b           != 255) currentStatus->b           = (digitalRead(inputs.b)           == LOW);
    if (inputs.x           != 255) currentStatus->x           = (digitalRead(inputs.x)           == LOW);
    if (inputs.y           != 255) currentStatus->y           = (digitalRead(inputs.y)           == LOW);
    if (inputs.l1          != 255) currentStatus->l1          = (digitalRead(inputs.l1)          == LOW);
    if (inputs.r1          != 255) currentStatus->r1          = (digitalRead(inputs.r1)          == LOW);
    if (inputs.l2          != 255) currentStatus->l2          = (digitalRead(inputs.l2)          == LOW);
    if (inputs.r2          != 255) currentStatus->r2          = (digitalRead(inputs.r2)          == LOW);
    if (inputs.lightshield != 255) currentStatus->lightshield = (digitalRead(inputs.lightshield) == LOW);
    if (inputs.midshield   != 255) currentStatus->midshield   = (digitalRead(inputs.midshield)   == LOW);

}

void setMultiplexer(int multiplexer, bool button1, bool button2, bool defaultValue) {
    
    if (multiplexer != 255) {
        pinMode(multiplexer, OUTPUT);

        if (button1 && button2)
            digitalWrite(multiplexer, !defaultValue);
        else
            digitalWrite(multiplexer, defaultValue);
    }
    
}

// This sort of works, but USB detection is more reliable
// bool detectJoyBus(int dataPin) {
//     pinMode(dataPin, INPUT_PULLUP);
//     bool detected = false;

//     for(int i = 0; i <= 1000; i++) {
//         detected = (digitalRead(dataPin) == LOW);
        
//         if (detected == true)
//             break;
//     }

//     return detected;
// }

bool detectUSB() {
    #if defined(HAS_USB)
        if (UDADDR & _BV(ADDEN))
            return true;
        else
            return false;
    #else
        return false;
    #endif
}

void sysDelay(int milliseconds) {
    delay(milliseconds);
}

#endif