#ifndef FLAPPY_BACK_CHARACTERDRAWER_H
#define FLAPPY_BACK_CHARACTERDRAWER_H

#include "yahal_String.h"
#include "st7735s_drv.h"
#include "vector"
#include "map"

struct CharacterPattern {
    const char* pattern[5];
};

class CharacterDrawer {
private:
    std::map<char, CharacterPattern> characters;
    st7735s_drv _lcd;

public:
    CharacterDrawer(st7735s_drv &lcd);
    void drawSymbol(char character, int x, int y, int size, color_t color);
    void drawWord(const char* word, int x, int y, int size, color_t color);
};

#endif //FLAPPY_BACK_CHARACTERDRAWER_H
