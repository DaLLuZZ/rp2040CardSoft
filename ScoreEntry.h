#ifndef FLAPPY_BACK_SCOREENTRY_H
#define FLAPPY_BACK_SCOREENTRY_H

#include "vector"
#include "spi_rp2040.h"

class ScoreEntry {
public:
    uint16_t _score;
    const char* _name;
    const char* _kzl;

    ScoreEntry(const char* name, const char* kzl, uint16_t score);
};

class Scoreboard {
public:
    std::vector<ScoreEntry> scores;
    Scoreboard();
    void updateScores(const ScoreEntry& newScore);
};


#endif //FLAPPY_BACK_SCOREENTRY_H
