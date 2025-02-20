#include "ScoreEntry.h"

//class for each set score
ScoreEntry::ScoreEntry(const char* name, const char* kzl, uint16_t score)
        : _name(name), _score(score), _kzl(kzl) {
}

//class for a set of 10 scores
Scoreboard::Scoreboard() {
    for(int i = 0; i < 10; i++) {
        updateScores(ScoreEntry("AAA", "EZ", 0));
    }
}

// function to update scores with a new one
void Scoreboard::updateScores(const ScoreEntry& newScore) {
    auto it = scores.begin();
    while (it != scores.end() && newScore._score <= it->_score) {
        ++it;
    }
    scores.insert(it, newScore);
    if (scores.size() > 10) {
        scores.pop_back();
    }
}
