#include "score.h"

score::score(string playerName)
{
    this->scoreValue = 0;
    this->playerName = playerName;
}
int score::readScore()
{
    return this->scoreValue;
}

void score::incScore(int increment)
{
    this->scoreValue += increment;
}

void score::rstScore()
{
    this->scoreValue = 0;
}

string score::readPlayerName()
{
    return this->playerName;
}

void score::redrawScore()
{


}
