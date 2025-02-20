#ifndef FLAPPY_BACK_DIFFICULTY_H
#define FLAPPY_BACK_DIFFICULTY_H

#include "st7735s_drv.h"

class Difficulty {
public:
    const char* _name;
    const char* _kzl;
    int _diff;
    int _x;
    int _y;
    color_t _color;

    // Konstruktor
    Difficulty(const char* name, const char* kzl, int d, int x, int y, color_t color);
};


#endif //FLAPPY_BACK_DIFFICULTY_H
