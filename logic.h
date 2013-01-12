#pragma once
#include "game.h"
#include "main.h"


class logic
{
friend class control;
friend class canvas;
private:

    game *gameParent;

    int gameState;
    int gameLoopSpeed;
    int tickSpeed;
    int counter=1;
    int m, n;  // Track new shape
    int newShapeType;
    int newShapeColor;
    int nextShapeType;
    int nextShapeColor;

    /* Block matrix control */

    void newShape(int newShapeType);
    bool collideDetect();
    void setAllStoned();
    void moveBlock(int x1, int y1, int x2, int y2);
    void goDown();

    void destroyLine();

public:
    void gameLogicIteration();

    int get_nextShapeType();
    void set_nextShapeType(int nextShapeType);

    int get_nextShapeColor();
    void set_nextShapeColor(int newShapeColor);

    void rotateShape();
    void moveLeft();
    void moveRight();
    void clearBlock();
    void resetState();

    logic(game *gameParent);

    // Debug
    // void printMatrices();

};
