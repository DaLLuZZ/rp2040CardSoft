#ifndef FLAPPY_BACK_GAME_H
#define FLAPPY_BACK_GAME_H

#include <cstdlib>
#include "gpio_rp2040.h"
#include <cstdio>
#include "timer_rp2040.h"
#include "uGUI_colors.h"
#include "spi_rp2040.h"
#include "st7735s_drv.h"
#include "adc_rp2040.h"
#include <inttypes.h>
#include "CharacterDrawer.h"
#include "yahal_String.h"
#include "Difficulty.h"
#include "ScoreEntry.h"
#include "GetColors.h"

class Game {
public:
    Game();

    void run();

private:
    gpio_rp2040_pin _lcd_cs;
    spi_rp2040  _spi;
    gpio_rp2040_pin _lcd_rst;
    gpio_rp2040_pin _lcd_dc;
    st7735s_drv _lcd;
    gpio_rp2040_pin _s1;
    gpio_rp2040_pin _s2;
    timer_rp2040 _timer;
    adc_rp2040_channel _accel_x;

    GetColors _getColors;

    char _name[4];
    Difficulty _diff;

    Scoreboard _sb;

    uint32_t _mode;

    CharacterDrawer _cd;

    void read_area_and_get_color(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);

    void drawBird(uint16_t birdPos);

    void play_mode();

    void menu_mode();

    void score_mode();

    void difficulty_mode();

    void setting_mode();

    void name_mode();

    bool check_collision(uint32_t r1, uint32_t r2, uint32_t r3, uint32_t r_x, uint32_t bird, uint16_t &_score);

    static void death_screen(st7735s_drv &lcd, timer_rp2040 &t);

    color_t color(int i);
};


#endif //FLAPPY_BACK_GAME_H
