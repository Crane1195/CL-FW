#ifndef CLFW_DAC_H
#define CLFW_DAC_H

#include "../Classes/ControllerStatus.h"
#include "../Classes/Coordinates.h"
#include "../Classes/Modes.h"

int fTwoIPNoR(bool isLOW, bool isHIGH, bool *wasLOW, bool *wasHIGH, bool *lockLOW, bool *lockHIGH);
int fTwoIP(bool isLOW, bool isHIGH, bool *wasLOW, bool *wasHIGH);
int fNeutral(bool isLOW, bool isHIGH);


outputStatus rectangleDAC(inputStatus *inputs, coordinates currentCoords, SOCD leftXSOCD, SOCD leftYSOCD, SOCD rightXSOCD, SOCD rightYSOCD) {
    
    outputStatus returnStatus;
    bool HORIZONTAL = false, VERTICAL = false, DIAGONAL = false;
    int positionX = 0, positionY = 0, positionCX = 0, positionCY = 0;

    int minValue = currentCoords.neutral - currentCoords.maxOffset;
    int maxValue = currentCoords.neutral + currentCoords.maxOffset;

    returnStatus.leftStickX = currentCoords.neutral;
    returnStatus.leftStickY = currentCoords.neutral;
    returnStatus.rightStickX = currentCoords.neutral;
    returnStatus.rightStickY = currentCoords.neutral;

    //****************************************************************************//
    // SOCD resolution for all four axes

    switch (leftXSOCD) {
        case TwoIPNoR:
            positionX = fTwoIPNoR(inputs->l_Left, inputs->l_Right, &inputs->l_Was_Left, &inputs->l_Was_Right, &inputs->l_Lock_Left, &inputs->l_Lock_Right); break;
        case TwoIP:
            positionX = fTwoIP(inputs->l_Left, inputs->l_Right, &inputs->l_Was_Left, &inputs->l_Was_Right); break;
        case Neutral:    
            positionX = fNeutral(inputs->l_Left, inputs->l_Right); break;
        default :
            break;
    }

    switch (leftYSOCD) {
        case TwoIPNoR:
            positionY = fTwoIPNoR(inputs->l_Down, inputs->l_Up, &inputs->l_Was_Down, &inputs->l_Was_Up, &inputs->l_Lock_Down, &inputs->l_Lock_Up); break;
        case TwoIP:
            positionY = fTwoIP(inputs->l_Down, inputs->l_Up, &inputs->l_Was_Down, &inputs->l_Was_Up); break;
        case Neutral:
            positionY = fNeutral(inputs->l_Down, inputs->l_Up); break;
        default :
            break;
    }

    switch (rightXSOCD) {
        case TwoIPNoR:
            positionCX = fTwoIPNoR(inputs->r_Left, inputs->r_Right, &inputs->r_Was_Left, &inputs->r_Was_Right, &inputs->r_Lock_Left, &inputs->r_Lock_Right); break;
        case TwoIP:
            positionCX = fTwoIP(inputs->r_Left, inputs->r_Right, &inputs->r_Was_Left, &inputs->r_Was_Right); break;
        case Neutral:
            positionCX = fNeutral(inputs->r_Left, inputs->r_Right); break;
        default :
            break;
    }

    switch (rightYSOCD) {
        case TwoIPNoR:
            positionCY = fTwoIPNoR(inputs->r_Down, inputs->r_Up, &inputs->r_Was_Down, &inputs->r_Was_Up, &inputs->r_Lock_Down, &inputs->r_Lock_Up); break;
        case TwoIP:
            positionCY = fTwoIP(inputs->r_Down, inputs->r_Up, &inputs->r_Was_Down, &inputs->r_Was_Up); break;
        case Neutral:
            positionCY = fNeutral(inputs->r_Down, inputs->r_Up); break;
        default :
            break;
    }

    //****************************************************************************//
    // Stick positions

    if (positionX != 0)
        HORIZONTAL = true;
    if (positionY != 0)
        VERTICAL = true;
    
    if (HORIZONTAL && VERTICAL) DIAGONAL = true;

    if      (positionCX ==  1) returnStatus.rightStickX = maxValue;
    else if (positionCX == -1) returnStatus.rightStickX = minValue;

    if      (positionCY ==  1) returnStatus.rightStickY = maxValue;
    else if (positionCY == -1) returnStatus.rightStickY = minValue;

    //****************************************************************************//
    // Modifiers

    // If no modifiers are held
    if (!inputs->modX && !inputs->modY) {
        if (HORIZONTAL && !DIAGONAL) {
            returnStatus.leftStickX += (positionX * currentCoords.maxOffset);
        }
        else if (VERTICAL && !DIAGONAL) {
            returnStatus.leftStickY += (positionY * currentCoords.maxOffset);
        }
        else if (DIAGONAL) {

            if (inputs->l2 || inputs->r2 || inputs->lightshield || inputs->midshield) {
                returnStatus.leftStickX += (positionX * currentCoords.diagonal_Shield.x);
                returnStatus.leftStickY += (positionY * currentCoords.diagonal_Shield.y);
            }
            else {
                returnStatus.leftStickX += (positionX * currentCoords.diagonal.x);
                returnStatus.leftStickY += (positionY * currentCoords.diagonal.y);
            }
        }
    }
    // If modX but not modY is held
    else if (inputs->modX && !inputs->modY) {
        if (HORIZONTAL && !DIAGONAL) {
            if (!inputs->b)
                returnStatus.leftStickX += (positionX * currentCoords.modX_Horizontal.x);
            else
                returnStatus.leftStickX += (positionX * currentCoords.modX_Horizontal_B.x);
        }
        else if (VERTICAL && !DIAGONAL) {
            if (!inputs->b)
                returnStatus.leftStickY += (positionY * currentCoords.modX_Vertical.y);
            else
                returnStatus.leftStickY += (positionY * currentCoords.modX_Vertical_B.y);
        }
        else if (DIAGONAL) {
            // Wavedash
            if (inputs->r2 || inputs->l2 || inputs->lightshield || inputs->midshield) {
                returnStatus.leftStickX += (positionX * currentCoords.modX_Diagonal_Shield.x);
                returnStatus.leftStickY += (positionY * currentCoords.modX_Diagonal_Shield.y);
            }
            else {
                // FFox modX cDown
                if (inputs->r_Down) {
                    if (!inputs->b) {
                        returnStatus.leftStickX += (positionX * currentCoords.modX_Diagonal_cDown.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modX_Diagonal_cDown.y);
                    }
                    else {
                        returnStatus.leftStickX += (positionX * currentCoords.modX_Diagonal_cDown_B.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modX_Diagonal_cDown_B.y);
                    }
                }
                // FFox modX cLeft
                else if (inputs->r_Left) {
                    if (!inputs->b) {
                        returnStatus.leftStickX += (positionX * currentCoords.modX_Diagonal_cLeft.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modX_Diagonal_cLeft.y);
                    }
                    else {
                        returnStatus.leftStickX += (positionX * currentCoords.modX_Diagonal_cLeft_B.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modX_Diagonal_cLeft_B.y);
                    }
                }
                // FFox modX cUp
                else if (inputs->r_Up) {
                    if (!inputs->b) {
                        returnStatus.leftStickX += (positionX * currentCoords.modX_Diagonal_cUp.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modX_Diagonal_cUp.y);
                    }
                    else {
                        returnStatus.leftStickX += (positionX * currentCoords.modX_Diagonal_cUp_B.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modX_Diagonal_cUp_B.y);
                    }
                }
                // FFox modX cLeft
                else if (inputs->r_Right) {
                    if (!inputs->b) {
                        returnStatus.leftStickX += (positionX * currentCoords.modX_Diagonal_cRight.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modX_Diagonal_cRight.y);
                    }
                    else {
                        returnStatus.leftStickX += (positionX * currentCoords.modX_Diagonal_cRight_B.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modX_Diagonal_cRight_B.y);
                    }
                }
                // Tilt angle
                else {
                    returnStatus.leftStickX += (positionX * currentCoords.modX_Diagonal.x);
                    returnStatus.leftStickY += (positionY * currentCoords.modX_Diagonal.y);
                }
            }
        }

        if (positionCX != 0) {
            returnStatus.rightStickX = currentCoords.neutral + (positionCX * currentCoords.modX_Angled_FSmash.x);
            returnStatus.rightStickY = currentCoords.neutral + (positionY * currentCoords.modX_Angled_FSmash.y);
        }    
    }
    // If modY but not modX is held
    else if (!inputs->modX && inputs->modY) {
        if (HORIZONTAL && !DIAGONAL) {
            if (!inputs->b)
                returnStatus.leftStickX += (positionX * currentCoords.modY_Horizontal.x);
            else
                returnStatus.leftStickX += (positionX * currentCoords.modY_Horizontal_B.x);
        }
        else if (VERTICAL && !DIAGONAL) {
            if (!inputs->b)
                returnStatus.leftStickY += (positionY * currentCoords.modY_Vertical.y);
            else
                returnStatus.leftStickY += (positionY * currentCoords.modY_Vertical_B.y);
        }
        else if (DIAGONAL) {
            // Wavedash
            if (inputs->r2 || inputs->l2) {
                returnStatus.leftStickX += (positionX * currentCoords.modY_Diagonal_Shield.x);
                returnStatus.leftStickY += (positionY * currentCoords.modY_Diagonal_Shield.y);
            }
            else {
                // FFox modY cDown
                if (inputs->r_Down) {
                    if (!inputs->b) {
                        returnStatus.leftStickX += (positionX * currentCoords.modY_Diagonal_cDown.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modY_Diagonal_cDown.y);
                    }
                    else {
                        returnStatus.leftStickX += (positionX * currentCoords.modY_Diagonal_cDown_B.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modY_Diagonal_cDown_B.y);
                    }
                }
                // FFox modY cLeft
                else if (inputs->r_Left) {
                    if (!inputs->b) {
                        returnStatus.leftStickX += (positionX * currentCoords.modY_Diagonal_cLeft.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modY_Diagonal_cLeft.y);
                    }
                    else {
                        returnStatus.leftStickX += (positionX * currentCoords.modY_Diagonal_cLeft_B.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modY_Diagonal_cLeft_B.y);
                    }
                }
                // FFox modY cUp
                else if (inputs->r_Up) {
                    if (!inputs->b) {
                        returnStatus.leftStickX += (positionX * currentCoords.modY_Diagonal_cUp.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modY_Diagonal_cUp.y);
                    }
                    else {
                        returnStatus.leftStickX += (positionX * currentCoords.modY_Diagonal_cUp_B.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modY_Diagonal_cUp_B.y);
                    }
                }
                // FFox modY cLeft
                else if (inputs->r_Right) {
                    if (!inputs->b) {
                        returnStatus.leftStickX += (positionX * currentCoords.modY_Diagonal_cRight.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modY_Diagonal_cRight.y);
                    }
                    else {
                        returnStatus.leftStickX += (positionX * currentCoords.modY_Diagonal_cRight_B.x);
                        returnStatus.leftStickY += (positionY * currentCoords.modY_Diagonal_cRight_B.y);
                    }
                }
                // Tilt angle
                else {
                    returnStatus.leftStickX += (positionX * currentCoords.modY_Diagonal.x);
                    returnStatus.leftStickY += (positionY * currentCoords.modY_Diagonal.y);
                }
            }
        }  
    }
    // If both mods are held
    else if (inputs->modX && inputs->modY) {
        // Disable CStick so the dpad will work as intended.
        returnStatus.rightStickX = currentCoords.neutral;
        returnStatus.rightStickY = currentCoords.neutral;
    }

    return returnStatus;
}

void digitalHandler(inputStatus *inputs, SOCD leftXSOCD, SOCD leftYSOCD, bool prioritizeUp) {

    int positionX = 0, positionY = 0;

    switch (leftXSOCD) {
        case TwoIPNoR:
            positionX = fTwoIPNoR(inputs->l_Left, inputs->l_Right, &inputs->l_Was_Left, &inputs->l_Was_Right, &inputs->l_Lock_Left, &inputs->l_Lock_Right); break;
        case TwoIP:
            positionX = fTwoIP(inputs->l_Left, inputs->l_Right, &inputs->l_Was_Left, &inputs->l_Was_Right); break;
        case Neutral:    
            positionX = fNeutral(inputs->l_Left, inputs->l_Right); break;
        default:
            break;
    }

    switch (leftYSOCD) {
        case TwoIPNoR:
            positionY = fTwoIPNoR(inputs->l_Down, inputs->l_Up, &inputs->l_Was_Down, &inputs->l_Was_Up, &inputs->l_Lock_Down, &inputs->l_Lock_Up); break;
        case TwoIP:
            positionY = fTwoIP(inputs->l_Down, inputs->l_Up, &inputs->l_Was_Down, &inputs->l_Was_Up); break;
        case Neutral:
            positionY = fNeutral(inputs->l_Down, inputs->l_Up); break;
        default:
            break;
    }
    
    if (leftXSOCD != NormalKeyboard) {
        if (positionX == 1) {
            inputs->l_Left = false;
            inputs->l_Right = true;
        }
        else if (positionX == -1) {
            inputs->l_Left = true;
            inputs->l_Right = false;
        }
        else {
            inputs->l_Left = false;
            inputs->l_Right = false;
        }
    }

    if (prioritizeUp && inputs->l_Up && inputs->l_Down) {
        inputs->l_Up   = true;
        inputs->l_Down = false;

        return;
    }

    if (leftYSOCD != NormalKeyboard) {
        if (positionY == 1) {
            inputs->l_Up = false;
            inputs->l_Down = true;
        }
        else if (positionY == -1) {
            inputs->l_Up = true;
            inputs->l_Down = false;
        }
        else {
            inputs->l_Up = false;
            inputs->l_Down = false;
        }
    }
    
}

int fTwoIPNoR(bool isLOW, bool isHIGH, bool *wasLOW, bool *wasHIGH, bool *lockLOW, bool *lockHIGH) {
    int position = 0;
    if (isLOW && isHIGH) {
        if (*wasHIGH) {
            position = -1;
            *lockHIGH = true; }
        if (*wasLOW) {
            position = 1;
            *lockLOW = true; }
    }
    if (!isLOW && isHIGH && (*lockHIGH == false)) {
        position = 1;
        *wasHIGH = true;
        *wasLOW = false;
        *lockLOW = false;
    }
    if (isLOW && !isHIGH && (*lockLOW == false)) {
        position = -1;
        *wasLOW = true;
        *wasHIGH = false;
        *lockHIGH = false;
    }
    if (!isLOW && !isHIGH) {
        *wasHIGH = false;
        *wasLOW = false;
        *lockLOW = false;
        *lockHIGH = false;
    }
    return position;
}

int fTwoIP(bool isLOW, bool isHIGH, bool *wasLOW, bool *wasHIGH) {
    int position = 0;
    if (isLOW && *wasHIGH)
        position = -1;
    if (isHIGH && *wasLOW)
        position = 1;
    if (!isLOW && isHIGH) {
        position = 1;
        *wasHIGH = true;
        *wasLOW = false; }
    if (isLOW && !isHIGH) {
        position = -1;
        *wasLOW = true;
        *wasHIGH = false;
    }
    return position;
}

int fNeutral(bool isLOW, bool isHIGH) {
    int position = 0;
    if (!isLOW && isHIGH)
        position = 1;
    if (isLOW && !isHIGH)
        position = -1;
    return position;
}


#endif
