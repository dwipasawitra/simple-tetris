#pragma once
#include "main.h"
#include "block.h"

class nextshape
{
private:
    int nextShapeType;
    int nextShapeColor;
    block *nextShapeBlock[4][4];
    BITMAP *nextShapeBorder;
public:
    void setNextShapeType(int nextShapeType, int nextShapeColor);
    int getNextShapeType();
    void redrawNextShape();
    nextshape();
};

