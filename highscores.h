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
    highscore() { };

};


class interfaceHighScore : public highscore
{
public:
    void displayHighScore() { };
};
