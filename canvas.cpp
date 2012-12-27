#include "canvas.h"

canvas::canvas(game *gameParent)
{
    this->gameParent = gameParent;
}

void canvas::redrawGraphic()
{
    // Redraw algorithm
    // Check all matrix content
    // Check if there is a block in graphic
    //
    // Yes: Keep it when matrix cell present
    //      Remove it when matrix cell doesn't present
    // No:  Draw it when matrix cell present
    //      Keep it when matrix cell doesn't present

    int i, j;

    // Iterator
    for(i=0;i<GAME_MAX_X;i++)
    {
        for(j=0;j<GAME_MAX_Y;j++)
        {
            if(this->checkPoint(i, j))
            {
                if(gameParent->gameBlock[i][j] == NULL)
                {
                    this->clearBlock(i, j);
                }
            }
            else if(gameParent->gameBlock[i][j] != NULL)
            {
                this->drawBlock(i, j, gameParent->gameBlock[i][j]);
            }
        }
    }
}

void canvas::drawBlock(int x, int y, block *property)
{
    int drawPointX, drawPointY;
    int blockColor;

    // If Y-axis is 0 to 3, you can't draw it
    if(y>=0 && y<=3)
    {
        return;
    }
    else
    {
        y = y-4;
    }

    // drawPoint = Center point of each block
    drawPointX = (20*x + 10) + GAME_CANVAS_START_X;
    drawPointY = (20*y + 10) + GAME_CANVAS_START_Y;

    // From center point, draw the 20x20 box;
    blockColor = property->getColor();

    //rectfill(screen, drawPointX-10, drawPointY-10, drawPointX+10, drawPointX+10, blockColor);
    circlefill(screen, drawPointX, drawPointY, 9, blockColor);

    // Done
}

void canvas::clearBlock(int x, int y)
{
    int drawPointX, drawPointY;

    // If Y-axis is 0 to 3, you can't draw it
    if(y>=0 && y<=3)
    {
        return;
    }
    else
    {
        y = y-4;
    }

    // drawPoint = Center point of each block
    drawPointX = (20*x + 10) + GAME_CANVAS_START_X;
    drawPointY = (20*y + 10) + GAME_CANVAS_START_Y;

    // From center point, clear its 20x20 box;
    //rectfill(screen, drawPointX-10, drawPointY-10, 20, 20, GAME_CANVAS_BACKGROUND);
    //rectfill(screen, drawPointX-10, drawPointY-10, drawPointX+10, drawPointX+10, GAME_CANVAS_BACKGROUND);
    circlefill(screen, drawPointX, drawPointY, 9, GAME_CANVAS_BACKGROUND);

    // Done
}

bool canvas::checkPoint(int x, int y)
{
    int checkPointX, checkPointY;

    // If Y-axis is 0 to 3, you can't draw it
    if(y>=0 && y<=3)
    {
        return 1;
    }
    else
    {
        y = y-4;
    }

    // checkPoint = Center point of each block
    checkPointX = (20*x + 10) + GAME_CANVAS_START_X;
    checkPointY = (20*y + 10) + GAME_CANVAS_START_Y;

    // Check if there is something other than GAME_CANVAS_BACKGROUND in drawPoint
    if(getpixel(screen, checkPointX, checkPointY) == GAME_CANVAS_BACKGROUND)
    {
        //cout << "CANVAS: Point " << checkPointX << "," << checkPointY << " does have GAME_CANVAS_BACKGROUND" << endl;
        return 0;
    }
    else
    {
        return 1;
    }
}
