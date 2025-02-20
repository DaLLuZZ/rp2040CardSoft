#ifndef GETCOLORS_H
#define GETCOLORS_H

#include <cstdint>
#include "st7735s_drv.h"

class GetColors {
private:
    st7735s_drv _lcd;
    uint32_t _Background[16384];
public:
    GetColors(st7735s_drv &lcd);
    uint16_t GetBackgroundPixel(int x, int y);
    void SetBackground();
};

#endif // GETCOLORS_H
