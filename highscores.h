#pragma once
#include "main.h"
#include "score.h"

class highscore
{
protected:
    list <score *> highScoreData;
    int totalEntry;

public:
    void reloadHighScore();
    static void newHighScore(score *newHighScore);
    void saveHighScore();
    void addScore(string playerName, int score);
    highscore() { };

};


class interfaceHighScore : public highscore
{
private:
    BITMAP *hsBackground;
    FONT *hsFont;
    PALLETE pallete;
public:
    void displayHighScore();
    interfaceHighScore();
};
