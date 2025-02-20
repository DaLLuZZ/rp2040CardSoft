#include "Difficulty.h"

    // class to set some difficulties
    Difficulty::Difficulty(const char* name, const char* kzl, int d, int x, int y, color_t color) :
            _name(name), _kzl(kzl), _diff(d), _x(x), _y(y), _color(color) {}
