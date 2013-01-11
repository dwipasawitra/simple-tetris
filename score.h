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

public:
    int readScore();
    void incScore(int increment);
    void rstScore();
    void redrawScore();

    string readPlayerName();

    score(string playerName);
    score(string playerName, int score);

};
