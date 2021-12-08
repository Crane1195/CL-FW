#ifndef CLFW_CONTROLLERSTATUS_H
#define CLFW_CONTROLLERSTATUS_H

struct inputStatus {
    // Left Stick
        bool l_Up;
        bool l_Down;
        bool l_Left;
        bool l_Right;

    // Right Stick
        bool r_Up;
        bool r_Down;
        bool r_Left;
        bool r_Right;

    // Variables used to track SOCD
        bool l_Was_Up;
        bool l_Was_Down;
        bool l_Was_Left;
        bool l_Was_Right;
        
        bool l_Lock_Up;
        bool l_Lock_Down;
        bool l_Lock_Left;
        bool l_Lock_Right;

        bool r_Was_Up;
        bool r_Was_Down;
        bool r_Was_Left;
        bool r_Was_Right;
        
        bool r_Lock_Up;
        bool r_Lock_Down;
        bool r_Lock_Left;
        bool r_Lock_Right;

    // Modifiers
        bool modX;
        bool modY;

    // Digital Buttons
        bool start;
        bool select;
        bool home;
    
        bool a;
        bool b;
        bool x;
        bool y;
        bool l1;
        bool r1;
        bool l2;
        bool r2;

        bool lightshield;
        bool midshield;
};

struct outputStatus {
    int leftStickX;
    int leftStickY;
    int rightStickX;
    int rightStickY;

    int triggerL;
    int triggerR;

    bool start;
    bool select;
    bool home;
    bool capture;
    bool touchpad;

    bool dpadUp;
    bool dpadDown;
    bool dpadLeft;
    bool dpadRight;

    bool a;
    bool b;
    bool x;
    bool y;
    bool l1;
    bool r1;
    bool l2;
    bool r2;
};

#endif