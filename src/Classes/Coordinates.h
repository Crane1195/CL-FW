#ifndef CLFW_COORDINATES_H
#define CLFW_COORDINATES_H

class coordinate{
public:
    coordinate() {
        x = 0;
        y = 0;
    }

    void set(int newX, int newY) {
        x = newX;
        y = newY;
    }

    int x;
    int y;
};

struct coordinates {
    int maxOffset;
    int neutral;

    // Max Values
    coordinate horizontal;
    coordinate vertical;
    coordinate diagonal;

    // Shield Drop
    coordinate diagonal_Shield;

    // ModX
        // Tilts
        coordinate modX_Horizontal;
        coordinate modX_Vertical;

        // Side B Nerf
        coordinate modX_Horizontal_B;
        coordinate modX_Vertical_B;

        // Up B Angles
        coordinate modX_Diagonal;
        coordinate modX_Diagonal_cDown;
        coordinate modX_Diagonal_cLeft;
        coordinate modX_Diagonal_cUp;
        coordinate modX_Diagonal_cRight;

        // Extended Up B Angles
        coordinate modX_Diagonal_B;
        coordinate modX_Diagonal_cDown_B;
        coordinate modX_Diagonal_cLeft_B;
        coordinate modX_Diagonal_cUp_B;
        coordinate modX_Diagonal_cRight_B;
        
        // Wavedash
        coordinate modX_Diagonal_Shield;

        // Angled FSmash
        coordinate modX_Angled_FSmash;

    // ModY
        // Tilts
        coordinate modY_Horizontal;
        coordinate modY_Vertical;

        // Side B Nerf
        coordinate modY_Horizontal_B;
        coordinate modY_Vertical_B;
        
        // Up B Angles
        coordinate modY_Diagonal;
        coordinate modY_Diagonal_cDown;
        coordinate modY_Diagonal_cLeft;
        coordinate modY_Diagonal_cUp;
        coordinate modY_Diagonal_cRight;

        // Extended Up B Angles
        coordinate modY_Diagonal_B;
        coordinate modY_Diagonal_cDown_B;
        coordinate modY_Diagonal_cLeft_B;
        coordinate modY_Diagonal_cUp_B;
        coordinate modY_Diagonal_cRight_B;

        // Wavedash
        coordinate modY_Diagonal_Shield;
};

#endif