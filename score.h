#include "main.h"

class score
{
private:
    BITMAP *scoreBorder;
    int gameScores;
public:
    void incScores(int increment);
    void setScores(int newScore);
    void clearScores();
    void redrawScores();
};
