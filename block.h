/*
 *
 * TETRIS VARIATION OF SHAPE
 *
 * {} = move point, tracked every new piece move
 * (m,n) = coordinate of move point
 *
 * ** Variation 1 **
 * A:  Draw (m-1,n)(m,n)(m+1,n)(m+2,n)
 * []{}[][]
 *
 * B:  Draw (m,n-1)(m,n)(m,n+1)(m,n+2)
 * []
 * {}
 * []
 * []
 *
 * ** Variaton 2 **
 * A:  Draw (m,n)(m+1,n)(m,n-1)(m+1,n+1)
 * []
 * {}[]
 *   []
 *
 * B:  Draw(m,n)(m-1,n)(m,n+1)(m+1,n+1)
 *
 * []{}
 *   [][]
 *
 * ** Variaton 3 **
 * A:  Draw (m,n)(m,n+1)(m-1,n)(m-1,n-1)
 * []
 * []{}
 *   []
 *
 * B:  Draw (m,n)(m-1,n)(m,n-1)(m+1,n-1)
 *   [][]
 * []{}
 *
 * ** Variation 4 **
 * A:  Draw (m,n)(m+1,n+1)(m+1,n)(m+1,n+1)
 * {}[]
 * [][]
 *
 */

#pragma once
#include "main.h"


class block
{
private:
    BITMAP *blockImage;
    int state;

public:
    int posX, posY;
    BITMAP *getImage();
    void setColor(int newColor);
    int getState();
    void setState(int newState);

    block(int newColor, int newState);
};



