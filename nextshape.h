#pragma once
#include "main.h"

class nextshape
{
private:
    int nextShapeType;
    BITMAP *nextShapeBorder;
public:
    void setNextShapeType();
    int getNextShapeType();
    void redrawNextShape();
};

