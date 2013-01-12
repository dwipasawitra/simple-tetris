#pragma once
#include "main.h"

class score
{
private:
    int scoreValue;
    string playerName;

    // Allegro drawing part
    BITMAP *scoreBorder;
    FONT *scoreFont;
    PALLETE pallete;

public:
    int readScore();
    void incScore(int increment);
    void rstScore();
    void redrawScore();

    string readPlayerName();

    // Score comparison operator
    bool operator==(const score &other) const;
    bool operator!=(const score &other) const;
    bool operator<(const score &other) const;
    bool operator<=(const score &other) const;
    bool operator>(const score &other) const;
    bool operator>=(const score &other) const;

    score(string playerName);
    score(string playerName, int score);

};
