
//****************************************************************************//
// Crane's Lab Firmware v0.1
// A modular, platform independent controller firmware by Crane.
//
// Documentation and latest releases can be found here:
//      https://github.com/Crane1195/CL-FW
//
//****************************************************************************//

#include "Classes/ControllerStatus.h"
#include "Classes/Modes.h"

#include "GameModes/Melee.h"
#include "GameModes/Ultimate.h"
#include "GameModes/PM.h"
#include "GameModes/RoA.h"
#include "GameModes/KBD.h"
#include "GameModes/FGC.h"

//****************************************************************************//
// Select your hardware platform

//--- Crane's Lab Hardware ---/
#if defined(HAS_GCCPCB_1)
    #include "Hardware/GCCPCB_1.h"
#elif defined(HAS_GCCPCB_2)
    #include "Hardware/GCCPCB_2.h"
#elif defined(HAS_GCCMX)
    #include "Hardware/GCCMX.h"
#elif defined(HAS_MODEL_S_2)
    #include "Hardware/Model_S_2.h"

//--- DIY Hardware ---//
#elif defined(HAS_ARDUINO)
    #include "Hardware/ArduinoDIY.h"

//--- SI Hardware ---//
#elif defined(HAS_B0XX_R1)
    #include "Hardware/B0XX_r1.h"
#elif defined(HAS_B0XX_R2)
    #include "Hardware/B0XX_r2.h"
#elif defined(HAS_HTANGL_V1)
    #include "Hardware/HTangl_V1.h"
#elif defined(HAS_HTANGL_PROTO)
    #include "Hardware/HTangl_Prototype.h"
#elif defined(HAS_SMASHBOX)
    #include "Hardware/Smashbox.h"
#elif defined(HAS_LBX)
    #include "Hardware/LBX.h"
#endif

CLFWController controller;

//****************************************************************************//
// AVR/Arduino Platform Dependencies
#if defined(HAS_AVR)
    #include "AVR_IO/AVR_GPIO.h"
    
    #if defined(HAS_JOYBUS)
        #include "AVR_IO/AVR_GCC.h"
        #include "AVR_IO/AVR_N64.h"
    #endif
    #if defined(HAS_USB)
        #include "AVR_IO/AVR_PCC.h"
        #include "AVR_IO/AVR_PCK.h"
        #include "AVR_IO/AVR_InputViewer.h"
    #endif
#endif 

//****************************************************************************//
// Select your SOCD                                    LeftX,    LeftY,   RightX,   RightY   Axes
meleeMode    meleeGameMode(controller.original_Pinout, TwoIPNoR, TwoIPNoR, TwoIPNoR, TwoIPNoR);
ultimateMode ultGameMode  (controller.original_Pinout, TwoIP   , TwoIP   , TwoIP   , TwoIP   );
PMMode       PMGameMode   (controller.original_Pinout, TwoIPNoR, TwoIPNoR, TwoIPNoR, TwoIPNoR);
RoAMode      RoAGameMode  (controller.original_Pinout, TwoIP   , TwoIP   , TwoIP   , TwoIP   );
// NASBMode  NASBGameMode (controller.original_Pinout, TwoIP   , TwoIP   , TwoIP   , TwoIP   );

//                                                                      true will make it so Up has priority over down. Change it to false if this isn't desired
FGCMode      FGCGameMode  (controller.original_Pinout, TwoIP   , TwoIP, true);

//                                                     true will make it so Up has priority over down. Change it to false if this isn't desired
KBDMode   KBDGameMode (NormalKeyboard, NormalKeyboard, true);

//****************************************************************************//
// Device managers

// TODO: Finish all the devices

#if defined(HAS_JOYBUS)
    GCController GCC;
    N64Controller N64C;
#endif

#if defined(HAS_USB)
    PCController PCC;
    //NSWController NSWC;
    PCKeyboard PCK;
#endif

//****************************************************************************//
// Status variables
device currentDevice;
game currentGame;
SOCD currentSOCD;

inputStatus buttonStatus;
outputStatus controlStatus;

//****************************************************************************//
// Setup runs once on plugin
void setup() {
    bool USBDetected = false;

    #if defined(HAS_USB)
        
        #if defined(HAS_AVR)
            // The AVR joystick library must be initialized before delays occur
            PCC.initialize();
        #endif

        // Delay used because USB comms do not start until a bit after the board receives power
        sysDelay(500);
        USBDetected = detectUSB();
    
    #endif

    // Set the button lines to INPUT_PULLUP
    initializeButtons(controller.original_Pinout);
    // Read in all of the buttons
    readAllButtons(&buttonStatus, controller.original_Pinout);

    // Set the USB multiplexer. By default you hold modX and A. Feel free to change this.
    // This will do nothing if you have the multiplexer set to 255 in your pinout.
    setMultiplexer(controller.multiplexer, buttonStatus.modX, buttonStatus.a, controller.defaultMUX);

    currentDevice = selectDevice(buttonStatus, controller.hasUSB, controller.consoleData, USBDetected);
    currentGame = selectGame(buttonStatus, currentDevice);

    // Run the initialization code for the selected device
    initializeDevice();
    // Set the current pinout to the pinout used by the current game
    initializeGame();
}

void loop() {
    // Read in all the buttons
    readAllButtons(&buttonStatus, controller.current_Pinout);

    // Update the output based on what game is being played
    updateOutput();

    // Send the output to the selected device
    sendOutput();
}

void initializeDevice() {

    // Initialize the selected device
    switch(currentDevice) {
        #if defined(HAS_JOYBUS)

            case GC :
                GCC.initialize(controller.consoleData, buttonStatus.start);  break;
            case N64 :
                N64C.initialize(controller.consoleData, buttonStatus.start); break;

        #endif
        #if defined(HAS_USB)

            case PC :
                if (PCC.initFlag == false)
                    PCC.initialize();

                break;
         // case NSWC :
         //     NSWC.initialize();                                     break;
            case KBD :
                PCK.initialize();                                      break;

        #endif

            default :
                break;
    }
}

void initializeGame() {

    // Set the controllers pinout to the pinout of the game being played
    switch(currentGame) {
        case Melee :
            controller.current_Pinout = meleeGameMode.current_Pinout;
            if (currentDevice == GC) GCC.setDelay(120); // Works on GC/Wii
            break;
        case Ultimate :
            controller.current_Pinout = ultGameMode.current_Pinout;     break;
        case PM :
            controller.current_Pinout = PMGameMode.current_Pinout;      break;
        case RoA :
            controller.current_Pinout = RoAGameMode.current_Pinout;     break;
        case FGC :
            controller.current_Pinout = FGCGameMode.current_Pinout;     break;
        case DefaultKBD :
            controller.current_Keymap = KBDGameMode.current_Keymap;     break;
        default :
            break;
    }

}

void updateOutput() {
    switch(currentGame) {
        case Melee :
            controlStatus = meleeGameMode.updateOutput(&buttonStatus);   break;
        case Ultimate :
            controlStatus = ultGameMode.updateOutput(&buttonStatus);     break;
        case PM :
            controlStatus = PMGameMode.updateOutput(&buttonStatus);      break;
        case RoA :
            controlStatus = RoAGameMode.updateOutput(&buttonStatus);     break;
        case FGC :
            controlStatus = FGCGameMode.updateOutput(&buttonStatus);     break;
        case DefaultKBD :
            KBDGameMode.updateOutput(&buttonStatus);                     break;
        default :
            break;
    }   
}

void sendOutput() {
    switch(currentDevice) {
        #if defined(HAS_JOYBUS)

            case GC :
                GCC.sendOutput(controlStatus); break;
            case N64 :
                N64C.sendOutput(controlStatus); break;

        #endif
        #if defined(HAS_USB)

            case PC :
                PCC.sendOutput(buttonStatus, controlStatus); break;
         // case NSWC :
         //     NSWC.sendOutput(controlStatus); break;
            case KBD :
                PCK.sendOutput(buttonStatus, controller.current_Keymap); break;

        #endif
        
            default :
                break;

    }
}