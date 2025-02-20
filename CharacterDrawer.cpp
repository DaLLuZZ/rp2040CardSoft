#include "CharacterDrawer.h"


// own Font, because the yahal font is deleting background behind each char
CharacterDrawer::CharacterDrawer(st7735s_drv &lcd) : _lcd(lcd) {
    // Initialisierung der Zeichenmuster für Zahlen und Buchstaben
    characters['A'] = {{"###", "# #", "###", "# #", "# #"}};
    characters['B'] = {{"###", "# #", "## ", "# #", "###"}};
    characters['C'] = {{"###", "#  ", "#  ", "#  ", "###"}};
    characters['D'] = {{"## ", "# #", "# #", "# #", "## "}};
    characters['E'] = {{"###", "#  ", "## ", "#  ", "###"}};
    characters['F'] = {{"###", "#  ", "## ", "#  ", "#  "}};
    characters['G'] = {{"###", "#  ", "# #", "# #", "###"}};
    characters['H'] = {{"# #", "# #", "###", "# #", "# #"}};
    characters['I'] = {{"###", " # ", " # ", " # ", "###"}};
    characters['J'] = {{"###", "  #", "  #", "# #", "###"}};
    characters['K'] = {{"# #", "## ", "## ", "# #", "# #"}};
    characters['L'] = {{"#  ", "#  ", "#  ", "#  ", "###"}};
    characters['M'] = {{"# #", "###", "# #", "# #", "# #"}};
    characters['N'] = {{"###", "# #", "# #", "# #", "# #"}};
    characters['O'] = {{"###", "# #", "# #", "# #", "###"}};
    characters['P'] = {{"## ", "# #", "###", "#  ", "#  "}};
    characters['Q'] = {{" # ", "# #", "# #", "## ", " ##"}};
    characters['R'] = {{"###", "# #", "###", "## ", "# #"}};
    characters['S'] = {{" ##", "#  ", " # ", "  #", "## "}};
    characters['T'] = {{"###", " # ", " # ", " # ", " # "}};
    characters['U'] = {{"# #", "# #", "# #", "# #", "###"}};
    characters['V'] = {{"# #", "# #", "# #", "# #", " # "}};
    characters['W'] = {{"# #", "# #", "# #", "###", "# #"}};
    characters['X'] = {{"# #", "# #", " # ", "# #", "# #"}};
    characters['Y'] = {{"# #", "# #", " # ", " # ", " # "}};
    characters['Z'] = {{"###", "  #", " # ", "#  ", "###"}};

    characters['0'] = {{"###", "# #", "# #", "# #", "###"}};
    characters['1'] = {{" # ", "## ", " # ", " # ", "###"}};
    characters['2'] = {{"###", "  #", "###", "#  ", "###"}};
    characters['3'] = {{"###", "  #", "###", "  #", "###"}};
    characters['4'] = {{"# #", "# #", "###", "  #", "  #"}};
    characters['5'] = {{"###", "#  ", "###", "  #", "###"}};
    characters['6'] = {{"###", "#  ", "###", "# #", "###"}};
    characters['7'] = {{"###", "  #", "  #", "  #", "  #"}};
    characters['8'] = {{"###", "# #", "###", "# #", "###"}};
    characters['9'] = {{"###", "# #", "###", "  #", "###"}};
}


// function to draw a single char
void CharacterDrawer::drawSymbol(char character, int x, int y, int size, color_t color) {
    const CharacterPattern& pattern = characters[character];
    for (int i = 0; i < 5; ++i) {
        for (size_t j = 0; pattern.pattern[i][j] != '\0'; ++j) {
            if (pattern.pattern[i][j] == '#') {
                // Die Koordinaten werden entsprechend der Größe skaliert
                for (int dy = 0; dy < size; ++dy) {
                    for (int dx = 0; dx < size; ++dx) {
                        _lcd.drawPixel(x + j * size + dx, y + i * size + dy, color);
                    }
                }
            }
        }
    }
}

// function to draw a word/char array
void CharacterDrawer::drawWord(const char* word, int x, int y, int size, color_t color) {
    for (int i = 0; word[i] != '\0'; ++i) {
        drawSymbol(word[i], x, y, size, color);
        x += 4 * size;
    }
}
