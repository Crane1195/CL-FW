#ifndef CLFW_AVR_PCK_H
#define CLFW_AVR_PCK_H

#include <Keyboard.h>
#include "./AVR_InputViewer.h"
#include "../Classes/ControllerStatus.h"
#include "../Classes/Pinout.h"

class PCKeyboard {
public:

    PCKeyboard() {

    }

    void initialize() {
        Keyboard.begin();

        IVCounter = 0;
        Serial.begin(115200, SERIAL_8N1);
    }

    void sendOutput (inputStatus inputs, pinout keyMap) {
        inputs.l_Up        ? Keyboard.press(keyMap.up         ) : Keyboard.release(keyMap.up         );
        inputs.l_Down      ? Keyboard.press(keyMap.down       ) : Keyboard.release(keyMap.down       );
        inputs.l_Left      ? Keyboard.press(keyMap.left       ) : Keyboard.release(keyMap.left       );
        inputs.l_Right     ? Keyboard.press(keyMap.right      ) : Keyboard.release(keyMap.right      );
        inputs.modX        ? Keyboard.press(keyMap.modX       ) : Keyboard.release(keyMap.modX       );
        inputs.modY        ? Keyboard.press(keyMap.modY       ) : Keyboard.release(keyMap.modY       );
        inputs.start       ? Keyboard.press(keyMap.start      ) : Keyboard.release(keyMap.start      );
        inputs.select      ? Keyboard.press(keyMap.select     ) : Keyboard.release(keyMap.select     );
        inputs.home        ? Keyboard.press(keyMap.home       ) : Keyboard.release(keyMap.home       );
        inputs.a           ? Keyboard.press(keyMap.a          ) : Keyboard.release(keyMap.a          );
        inputs.b           ? Keyboard.press(keyMap.b          ) : Keyboard.release(keyMap.b          );
        inputs.x           ? Keyboard.press(keyMap.x          ) : Keyboard.release(keyMap.x          );
        inputs.y           ? Keyboard.press(keyMap.y          ) : Keyboard.release(keyMap.y          );
        inputs.l1          ? Keyboard.press(keyMap.l1         ) : Keyboard.release(keyMap.l1         );
        inputs.r1          ? Keyboard.press(keyMap.r1         ) : Keyboard.release(keyMap.r1         );
        inputs.l2          ? Keyboard.press(keyMap.l2         ) : Keyboard.release(keyMap.l2         );
        inputs.r2          ? Keyboard.press(keyMap.r2         ) : Keyboard.release(keyMap.r2         );
        inputs.lightshield ? Keyboard.press(keyMap.lightshield) : Keyboard.release(keyMap.lightshield);
        inputs.midshield   ? Keyboard.press(keyMap.midshield  ) : Keyboard.release(keyMap.midshield  );
        inputs.r_Up        ? Keyboard.press(keyMap.cUp        ) : Keyboard.release(keyMap.cUp        );
        inputs.r_Down      ? Keyboard.press(keyMap.cDown      ) : Keyboard.release(keyMap.cDown      );
        inputs.r_Left      ? Keyboard.press(keyMap.cLeft      ) : Keyboard.release(keyMap.cLeft      );
        inputs.r_Right     ? Keyboard.press(keyMap.cRight     ) : Keyboard.release(keyMap.cRight     );

        sendIVData(inputs, &IVCounter);
    }

private:
    int IVCounter;

};


#endif