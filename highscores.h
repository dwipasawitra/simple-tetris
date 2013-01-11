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
    void newHighScore(score *newHighScore);
    void saveHighScore();
    void addScore(string playerName, int score);
    highscore() { };

};


class interfaceHighScore : public highscore
{
private:
    BITMAP *hsBackground;
public:
    void displayHighScore();
    interfaceHighScore();
};
