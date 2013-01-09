#pragma once
#include "game.h"
#include "block.h"

// Game canvas class
class canvas
{
private:
    game *gameParent;
    BITMAP *gameBorder;
public:
    void redrawGraphic();
    void drawBlock(int x, int y, block *property);
    void clearBlock(int x, int y);
    bool checkPoint(int x, int y);
    void redrawBorder();

    canvas(game *gameParent);
    ~canvas();
};
