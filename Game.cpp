#include "Game.h"

Game::Game() : _lcd_cs(5), _spi(0, 4, 7, 22, _lcd_cs), _lcd_rst(9),
         _lcd_dc (2), _lcd(_spi, _lcd_rst, _lcd_dc, st7735s_drv::Crystalfontz_128x128),
         _s1(16), _s2(17), _timer(2), _accel_x(0), _getColors(_lcd), _name("AAA"),
         _diff("MEDIUM", "MD", 16, 18, 64, C_YELLOW), _sb() ,_mode(0), _cd(_lcd)
{
    // using only one timer because 2 caused a lot of problems idk why

    _spi.setSpeed(30000000);
    _lcd.clearScreen(0x0);

    // accel axis for random level generation
    _accel_x.adcMode(ADC::ADC_12_BIT);
    srand(1000 * _accel_x.adcReadVoltage());

    _s1.gpioMode(GPIO::INPUT | GPIO::PULLUP);
    _s2.gpioMode(GPIO::INPUT | GPIO::PULLUP);

    // some scores so the scoreboard doesnt look too empty
    _sb.updateScores(ScoreEntry("ROB", "HR", 26));
    _sb.updateScores(ScoreEntry("ROB", "MD", 38));
    _sb.updateScores(ScoreEntry("JUL", "HR", 25));
    _sb.updateScores(ScoreEntry("JUL", "EX", 11));
}
// edit the pixel of an area to the background at this coordinates
void Game::read_area_and_get_color(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
    if(x1>x2)
    {
        int xx = x1;
        x1=x2;
        x2=xx;
    }
    if(y1>y2)
    {
        int yy = y1;
        y1=y2;
        y2=yy;
    }
    for(int x=x1; x<x2+1; x++)
    {
        for(int y=y1; y<y2+1; y++)
        {
            _lcd.drawPixel(x, y, _getColors.GetBackgroundPixel(x,y));
        }
    }
}
// draws the bird at the active position
void Game::drawBird(uint16_t birdPos) {
    for(int x=17; x<24; x++){
        for(int y=-3; y<4; y++){
            if(x==23 && (y==-2 || y==-1)){
                _lcd.drawPixel(x, birdPos + y, C_BLACK);
            }else if((((x==20)||(x==21))&&y==0)||(x==19 && y==-1)||(x==18 && y==-2)){
                _lcd.drawPixel(x, birdPos + y, 0x880B11);
            }else if((x==19||x==21)&&y==3){
                _lcd.drawPixel(x, birdPos + y, C_ORANGE);
            }else{
                _lcd.drawPixel(x, birdPos + y, 0xD2111B);
            }
        }
    }
}

void Game::run() {
    while(true){
        switch(_mode) {
            case 0:
                menu_mode();
                break;
            case 1:
                play_mode();
                break;
            case 2:
                score_mode();
                break;
            case 3:
                setting_mode();
                break;
            case 4:
                name_mode();
                break;
            case 5:
                difficulty_mode();
                break;
            default:
                _mode = 0;
                break;
        }
    }
}

// game mode, it's time to play
void Game::play_mode() {
    _getColors.SetBackground();

    uint16_t _score = 0;

    // pos bird (height)
    uint16_t  _bird_pos = 50;
    uint16_t _prev_pos = 64;
    uint16_t _bird_x = 4;

    // roehren
    uint16_t _r_x = 0;
    uint16_t _r1 = 999;
    uint16_t _r2 = 999;
    uint16_t _r3 = 999;

    // gameSpeed is getting incremented on timer callback and block set to false
    // because else if the while(true) is done, timer hasn't done a callback and
    // no block is set, it will do the things again -> we dont want that :)
    int gameSpeed = 0;
    bool block = true;

    // use callback to check input and trigger
    _timer.setPeriod(5000, TIMER::PERIODIC);
    _timer.setCallback([&]() {
        if(!_s1.gpioRead()) {
            _bird_x = 0;
        }
        gameSpeed += 1;
        block = false;
    });

    _timer.start();

    // loop for gaming mode
    while(true) {
        // block variable because of while(true), it happens that the if()... is faster than timer callback
        // so it runs too often
        if((gameSpeed % _diff._diff == 0) && !block) {
            block = true;
            _prev_pos = _bird_pos;
            // calc new bird pos, limit it to max 100 and min 3 (uint)
            if (((_bird_pos + (_bird_x - 3)) > 1000 || (_bird_pos + _bird_x - 3) < 3)) {
                _bird_pos = 3;
            } else if ((_bird_pos + _bird_x - 3) > 100) {
                _bird_pos = 100;
            } else {
                _bird_pos += _bird_x - 3;
            }

            // Logic for generating new Roehren position
            if (_r_x % 128 == 0) {
                _r1 = (rand() % 14) * 4 + 24;
            }
            if (_r_x % 128 == 85) {
                _r2 = (rand() % 14) * 4 + 24;
            }
            if (_r_x % 128 == 42) {
                _r3 = (rand() % 14) * 4 + 24;
            }

            // Delete old Roehren position and generate new
            read_area_and_get_color((_r_x % 128 + 8) - 1, 0, (_r_x % 128 + 8) - 1, 110);
            _lcd.fillArea((_r_x % 128) - 1, 0, (_r_x % 128) - 1, _r1 - 16, C_DARK_GREEN);
            _lcd.fillArea((_r_x % 128) - 1, _r1 + 16, (_r_x % 128) - 1, 110, C_DARK_GREEN);

            if (_r2 != 999) {
                read_area_and_get_color((_r_x % 128 + 8) + 42, 0, (_r_x % 128 + 8) + 42, 110);
                _lcd.fillArea((_r_x % 128) + 42, 0, (_r_x % 128) + 42, _r2 - 16, C_DARK_GREEN);
                _lcd.fillArea((_r_x % 128) + 42, _r2 + 16, (_r_x % 128) + 42, 110, C_DARK_GREEN);
            }
            if (_r3 != 999) {
                read_area_and_get_color((_r_x % 128 + 8) + 85, 0, (_r_x % 128 + 8) + 85, 110);
                _lcd.fillArea((_r_x % 128) + 85, 0, (_r_x % 128) + 85, _r3 - 16, C_DARK_GREEN);
                _lcd.fillArea((_r_x % 128) + 85, _r3 + 16, (_r_x % 128) + 85, 110, C_DARK_GREEN);
            }

            // draw bird if it moved
            if (_prev_pos != _bird_pos) {
                read_area_and_get_color(17, _prev_pos - 3, 23, _prev_pos + 3);
               drawBird(_bird_pos);
            }

            // Check for collision of bird with a Roehre
            if (check_collision(_r1, _r2, _r3, _r_x, _bird_pos, _score)) {
                _timer.stop();

                // add score
                _sb.updateScores(ScoreEntry(_name, _diff._kzl, _score));

                // little timer to see your big mistake
                _timer.setPeriod(2000000, TIMER::ONE_SHOT);
                _timer.setCallback([&]() {});
                _timer.start();
                while (_timer.isRunning()) {}

                _mode = 0;

                death_screen(_lcd, _timer);
                return;
            }

            // add score after passed roehre
            if(_r_x % 42 == 20) {
                String s = to_String(_score);
                // little calc to have the numbers always centered
                read_area_and_get_color(64 - (s.size() * 3 * 3 + 3 * (s.size() - 1)) / 2, 112,
                                        64 + (s.size() * 3 * 3 + 3 * (s.size() - 1)) / 2, 126);
                char const *score = s.c_str();
                printf("char c0 : %c , c1 : %c , score : %d \n", score[0], score[1], _score);
                _cd.drawWord(score, 64 - (s.size() * 3 * 3 + 3 * (s.size() - 1)) / 2, 112, 3, C_WHITE);
            }

            // Roehren x tick negative for moving from right to left
            _r_x--;
            _bird_x++;
        }
    }
}

// mode for settings
void Game::setting_mode() {
    bool input = false;
    uint8_t selected = 0;
    bool s1_still_holding = false;
    bool s2_still_holding = false;
    uint8_t timer = 0;
    bool timer_block = true;

    //_lcd.fillArea(0, 0, 127, 127, C_GOLD);
    _getColors.SetBackground();


    // callback for input
    _timer.setPeriod(25000, TIMER::PERIODIC);
    _timer.setCallback([&]() {
        printf("input? ");
        if(!_s1.gpioRead()) {
            if (!s1_still_holding) {
                input = true;
                s1_still_holding = true;
            }
        } else {
            s1_still_holding = false;
        }

        if(!_s2.gpioRead()){
            if(!s2_still_holding) {
                selected = (selected + 1) % 3;
                s2_still_holding = true;
            }
        } else {
            s2_still_holding = false;
        }
        timer_block = false;
        timer += 1;
    });

    _cd.drawWord("FLAPPY", 15, 5, 3, C_WHITE);
    _cd.drawWord("BIRB", 65, 25, 3, C_WHITE);
    _cd.drawWord("NAME", 38, 64, 3, C_WHITE);
    _cd.drawWord("DIFFICULTY", 9, 84, 3, C_WHITE);
    _cd.drawWord("BACK", 38, 104, 3, C_WHITE);

    int color[2] = {C_GREEN, C_WHITE};
    uint8_t current_color = 0;

    _timer.start();

    // selected and blinking animation
    while(_mode == 3){
        if(input) {
            _mode += selected +1;
        }
        if(timer % 10 == 0 && !timer_block && _mode == 3){
            current_color = (current_color + 1) % 2;
            printf("color set settings \n");
            if(selected == 0) {
                _cd.drawWord("NAME", 38, 64, 3, color[current_color]);
                _cd.drawWord("DIFFICULTY", 9, 84, 3, C_WHITE);
                _cd.drawWord("BACK", 38, 104, 3, C_WHITE);
            } else if (selected == 1){
                _cd.drawWord("NAME", 38, 64, 3, C_WHITE);
                _cd.drawWord("DIFFICULTY", 9, 84, 3, color[current_color]);
                _cd.drawWord("BACK", 38, 104, 3, C_WHITE);
            } else {
                _cd.drawWord("NAME", 38, 64, 3, C_WHITE);
                _cd.drawWord("DIFFICULTY", 9, 84, 3, C_WHITE);
                _cd.drawWord("BACK", 38, 104, 3, color[current_color]);
            }
            timer_block = true;
        }
    }
    _timer.stop();

    // little timer to make sure everything ended properly and better transition into new mode
    _timer.setPeriod(500000, TIMER::ONE_SHOT);
    _timer.start();
    while (_timer.isRunning()){
    }
}

// main menu/start screen
void Game::menu_mode() {
    bool input = false;
    bool s1_still_holding = false;
    bool s2_still_holding = false;
    uint8_t selected = 0;
    uint8_t timer = 0;
    bool timer_block = true;

    //we've seen this quiet some time
    _timer.setPeriod(25000, TIMER::PERIODIC);
    _timer.setCallback([&]() {
        if(!_s1.gpioRead()) {
            if (!s1_still_holding) {
                input = true;
                s1_still_holding = true;
            }
        } else {
            s1_still_holding = false;
        }

        if(!_s2.gpioRead()){
            if(!s2_still_holding) {
                selected = (selected + 1) % 3;
                s2_still_holding = true;
            }
        } else {
            s2_still_holding = false;
        }
        timer += 1;
        timer_block = false;
    });

    _getColors.SetBackground();

    // casual visualization
    _cd.drawWord("FLAPPY", 15, 5, 3, C_WHITE);
    _cd.drawWord("BIRB", 65, 25, 3, C_WHITE);
    _cd.drawWord("START", 35, 64, 3, C_WHITE);
    _cd.drawWord("SC0RE", 35, 84, 3, C_WHITE);
    _cd.drawWord("SETTINGS", 18, 104, 3, C_WHITE);
    _cd.drawWord(_name, 5, 35, 2, _diff._color);
    _cd.drawWord(_diff._kzl, 5, 47, 2, _diff._color);


    // to swap between green and white color on selected state
    int color[2] = {C_GREEN, C_WHITE};
    uint8_t current_color = 0;

    _timer.start();

    //similar to settings
    while(_mode == 0){
        if(input) {
            _mode = selected +1;
        }
        if(timer % 10 == 0 && !timer_block && _mode == 0) {
            current_color = (current_color + 1) % 2;
            if (selected == 0) {
                _cd.drawWord("START", 35, 64, 3, color[current_color]);
                _cd.drawWord("SC0RE", 35, 84, 3, C_WHITE);
                _cd.drawWord("SETTINGS", 18, 104, 3, C_WHITE);
            } else if (selected == 1) {
                _cd.drawWord("START", 35, 64, 3, C_WHITE);
                _cd.drawWord("SC0RE", 35, 84, 3, color[current_color]);
                _cd.drawWord("SETTINGS", 18, 104, 3, C_WHITE);
            } else {
                _cd.drawWord("START", 35, 64, 3, C_WHITE);
                _cd.drawWord("SC0RE", 35, 84, 3, C_WHITE);
                _cd.drawWord("SETTINGS", 18, 104, 3, color[current_color]);
            }
            timer_block = true;
        }
    }
    _timer.stop();

    // short delay because it bugged on changes
    _timer.setPeriod(500000, TIMER::ONE_SHOT);
    _timer.setCallback([&] {
    });
    _timer.start();
    while (_timer.isRunning()){
    }

}


// set your own name! WHAT? (or at least a short version of it)
void Game::name_mode() {
    bool input = false;
    bool changed = false;
    bool s1_still_holding = false;
    bool s2_still_holding = false;
    int selected = 0;
    int i = 0;
    int timer = 0;

    _getColors.SetBackground();

    // you again? (little diffrent today)
    _timer.setPeriod(25000, TIMER::PERIODIC);
    _timer.setCallback([&]() {
        if(!_s1.gpioRead()) {
            if (!s1_still_holding) {
                input = true;
                s1_still_holding = true;
            }
        } else {
            s1_still_holding = false;
        }
        if(!_s2.gpioRead()){
            if(!s2_still_holding) {
                selected = (selected + 1) % 36;
                s2_still_holding = true;
                changed = true;
            }
        } else {
            s2_still_holding = false;
        }
        timer += 1;
    });

    _timer.start();

    _cd.drawWord("FLAPPY", 15, 5, 3, C_WHITE);
    _cd.drawWord("BIRB", 65, 25, 3, C_WHITE);

    _cd.drawSymbol(_name[0], 34, 64, 5, C_GREEN);
    _cd.drawSymbol(_name[1], 54, 64, 5, C_WHITE);
    _cd.drawSymbol(_name[2], 74, 64, 5, C_WHITE);

    char c = (selected < 26) ? ('A' + selected) : ('0' + (selected - 26));

    //increment through 3 slots and change chars to letter or numbers
    while(_mode == 4){
        if(i == 3) {
            _timer.stop();
            _mode = 0;
            break;
        }
        if(timer % 10 == 0 && changed && !input) {
            read_area_and_get_color(34 + 20*i, 64, 49 + 20*i, 89);
            c = (selected < 26) ? ('A' + selected) : ('0' + (selected - 26));
            _cd.drawSymbol(c, 34 + 20*i, 64, 5, C_GREEN);
            changed = false;
        }
        if(input) {
            _cd.drawSymbol(c, 34 + 20*i, 64, 5, C_WHITE);
            _name[i] = c;
            printf("%c %c \n", _name[i], c);
            input = false;
            selected = 0;
            changed = true;
            i += 1;
        }
    }

    _timer.setPeriod(500000, TIMER::ONE_SHOT);
    _timer.start();
    while (_timer.isRunning()){
    }
}

// mode to select difficulties
void Game::difficulty_mode() {
    bool input = false;
    bool changed = false;
    bool s1_still_holding = false;
    bool s2_still_holding = false;
    int selected = 0;
    int timer = 0;

    _getColors.SetBackground();

    // the usual callback timer
    _timer.setPeriod(25000, TIMER::PERIODIC);
    _timer.setCallback([&]() {
        if(!_s1.gpioRead()) {
            if (!s1_still_holding) {
                input = true;
                s1_still_holding = true;
            }
        } else {
            s1_still_holding = false;
        }
        if(!_s2.gpioRead()){
            if(!s2_still_holding) {
                selected = (selected + 1) % 5;
                s2_still_holding = true;
                changed = true;
            }
        } else {
            s2_still_holding = false;
        }
        timer += 1;
    });

    _cd.drawWord("FLAPPY", 15, 5, 3, C_WHITE);
    _cd.drawWord("BIRB", 65, 25, 3, C_WHITE);


    // set difficulties the player can choose from
    Difficulty d[5] = {
            Difficulty("EASY", "EZ", 18, 34, 64, C_GREEN),
            Difficulty("MEDIUM", "MD", 12, 18, 64, C_YELLOW),
            Difficulty("HARD", "HR", 8, 34, 64, C_RED),
            Difficulty("EXTREME", "EX", 3, 10, 64, C_PURPLE),
            Difficulty("INSANE", "IN", 1, 18, 64, C_BLACK)
    };

    for(int n = 0; n < 5; n++) {
        if(_diff._name == d[n]._name) {
            selected = n;
            break;
        }
    }

    //current selected diff
    _cd.drawWord(d[selected]._name, d[selected]._x, d[selected]._y, 4, d[selected]._color);


    _timer.start();

    //while mode is 5(diff mode) change diff on screen, on input save it
    while(_mode == 5){
        if(timer % 20 == 0 && !input && changed) {
            read_area_and_get_color(10, 64, 118, 89);
            //_lcd.fillArea(10, 64, 118, 89, C_DARK_GRAY);
            changed = false;
            _cd.drawWord(d[selected]._name, d[selected]._x, d[selected]._y, 4, d[selected]._color);
        }
        if(input) {
            _diff = d[selected];
            _timer.stop();
            _mode = 0;
        }
    }

    //timer for cleaner flow into other modes
    _timer.setPeriod(500000, TIMER::ONE_SHOT);
    _timer.start();
    while (_timer.isRunning()){
    }
}


//showing highscores
void Game::score_mode() {
    bool input = false;

    // timer to exit highscore mode
    _timer.setPeriod(25000, TIMER::PERIODIC);
    _timer.setCallback([&]() {
        if(!_s1.gpioRead() || !_s2.gpioRead()) {
            input = true;
        }
    });

    _lcd.fillArea(0, 0, 127, 127, C_BLACK);
    _cd.drawWord("HIGHSCORES", 5, 0, 3, C_WHITE);

    // display all scores with color for 1-3
    for(int i = 0; i<10; i++) {
        // casting int to char
        String s = to_String(_sb.scores[i]._score);
        char const *score = s.c_str();

        String r = to_String(i + 1);
        char const *rank = r.c_str();

        _cd.drawWord(_sb.scores[i]._name, 22, 17 +11*i, 2, color(i));
        _cd.drawWord(rank, 5, 17 +11*i, 2, color(i));
        _cd.drawWord(_sb.scores[i]._kzl, 58, 17 +11*i, 2, color(i));
        _cd.drawWord(score, 82, 17 +11*i, 2, color(i));
        printf("Rank %d: Name %c%c%c, Diff %c%c, Score %d \n", i +1,_sb.scores[i]._name[0],_sb.scores[i]._name[1],
               _sb.scores[i]._name[2], _sb.scores[i]._kzl[0], _sb.scores[i]._kzl[1], _sb.scores[i]._score);
    }

    _timer.start();

    while(_mode == 2) {
        if(input) {
            _mode = 0;
        }
    }

    _timer.setPeriod(500000, TIMER::ONE_SHOT);
    _timer.start();
    while (_timer.isRunning()){
    }
}

//color for score placements
color_t Game::color(int i){
    switch (i) {
        case 0: return C_GOLD;
        case 1: return 0xC0C0C0;
        case 2: return 0x9C651F;
        default: return C_WHITE;
    }
}

//collision detection
bool Game::check_collision(uint32_t r1, uint32_t r2, uint32_t r3, uint32_t r_x, uint32_t bird, uint16_t &_score) {

    // check r1 is at bird pos
    if(((r_x % 128) >= 11 && (r_x % 128) <= 25) && r1 != 999) {

        // check bird is colliding with r1
        if(bird >= ( r1 + 12) || bird <= (r1 - 12)) {
            return true;
        }
        if(r_x % 14 == 0){
            _score += 1;
        }
        // check r2 at bird pos
    } else if(((r_x % 128) >=96 && (r_x % 128) <= 110) && r2 != 999) {

        // check r2 is colliding with r2
        if(bird >= ( r2 + 12) || bird <= (r2 - 12)) {
            return true;
        }
        if(r_x % 14 == 0){
            _score += 1;
        }
        // check r3 is at bird pos
    } else if(((r_x % 128) >=53 && (r_x % 128) <= 67) && r3 != 999) {

        // check bird is colliding with r3
        if(bird >= ( r3 + 12) || bird <= (r3 - 12)) {
            return true;
        }
        if(r_x % 14 == 0){
            _score += 1;
        }
    }
    return false;
}

// funny visual (yay)
void Game::death_screen(st7735s_drv &lcd, timer_rp2040 &t){
    t.setPeriod_ns(10000000, TIMER::ONE_SHOT);

    // filling screen red
    for(uint8_t i = 0; i<65; i++){
        lcd.fillArea(i, i, 127-i, i, C_RED);
        lcd.fillArea(127-i, i, 127-i, 127-i, C_RED);
        lcd.fillArea(i, 127-i, 127-i, 127-i, C_RED);
        lcd.fillArea(i, i, i, 127-i, C_RED);
        t.start();
        while(t.isRunning()){
        }
    }
    t.setPeriod_ns(1000000000, TIMER::ONE_SHOT);
    while (t.isRunning()){
    }
}
