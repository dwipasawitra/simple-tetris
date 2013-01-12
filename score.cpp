#include "score.h"

score::score(string playerName)
{
    this->scoreValue = 0;
    this->playerName = playerName;
    this->scoreBorder = load_bitmap("scoreboard.bmp", NULL);
    this->scoreFont = load_font("font-score.pcx", pallete, NULL);

}

score::score(string playerName, int score)
{
    this->playerName = playerName;
    this->scoreBorder = load_bitmap("scoreboard.bmp", NULL);
    this->scoreFont = load_font("font-score.pcx", pallete, NULL);
    this->scoreValue = score;
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
    // Draw score border
    blit(this->scoreBorder, screen, 0, 0, GAME_SCOREBOARD_START_X, GAME_SCOREBOARD_START_Y, GAME_SCOREBOARD_WIDTH, GAME_SCOREBOARD_HEIGHT);

    // Show player name
    textout_centre_ex(screen, this->scoreFont, this->playerName.c_str(), GAME_SCOREBOARD_START_X + GAME_SCOREBOARD_WIDTH / 2, GAME_SCOREBOARD_PLAYERNAME_Y, makecol(0,0,0), -1);

    // Show score
    char scoreValueStr[10];
    sprintf(scoreValueStr, "%05d", this->scoreValue);
    textout_centre_ex(screen, this->scoreFont, scoreValueStr, GAME_SCOREBOARD_START_X + GAME_SCOREBOARD_WIDTH / 2, GAME_SCOREBOARD_SCORE_Y, makecol(255,0,0), -1);
}

bool score::operator==(const score &other) const
{
    return (this->scoreValue==other.scoreValue);
}
bool score::operator!=(const score &other) const
{
    return (this->scoreValue!=other.scoreValue);
}
bool score::operator<(const score &other) const
{
    return (this->scoreValue<other.scoreValue);
}
bool score::operator<=(const score &other) const
{
    return (this->scoreValue<=other.scoreValue);
}
bool score::operator>(const score &other) const
{
    return (this->scoreValue>other.scoreValue);
}
bool score::operator>=(const score &other) const
{
    return (this->scoreValue>=other.scoreValue);
}
