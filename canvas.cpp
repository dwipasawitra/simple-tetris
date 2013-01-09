#include "canvas.h"

canvas::canvas(game *gameParent)
{
    this->gameParent = gameParent;
    this->gameBorder = load_bitmap("border.bmp", NULL);
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

    // NOT IMPLEMENTED YET, Using inefficient redrawing algorithm


    int i, j;

    /*
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
            else
            {
                if(gameParent->gameBlock[i][j] != NULL)
                {
                    this->drawBlock(i, j, gameParent->gameBlock[i][j]);
                }
            }
        }
    }
    */



    for(i=0;i<GAME_MAX_X;i++)
    {
        for(j=0;j<GAME_MAX_Y;j++)
        {
            if(gameParent->gameBlock[i][j] != NULL)
            {
                this->drawBlock(i, j, gameParent->gameBlock[i][j]);
            }
            else
            {
                this->clearBlock(i, j);
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

    // drawPoint = Left top point of each block
    drawPointX = (20*x) + GAME_CANVAS_START_X;
    drawPointY = (20*y) + GAME_CANVAS_START_Y;

    // From left top point, draw the image

    blit(property->getImage(), screen, 0, 0, drawPointX, drawPointY, 20, 20);

    // Save drawPoint on property
    // So we can check if there is a block on that point later
    //property->posX = drawPointX;
    //property->poxY = drawPointY;

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

    // drawPoint = left top point of each block
    drawPointX = (20*x) + GAME_CANVAS_START_X;
    drawPointY = (20*y) + GAME_CANVAS_START_Y;

    // From left top point, draw background in that position
    blit(gameParent->background, screen, drawPointX, drawPointY, drawPointX, drawPointY, 20, 20);

    // Done
}

// Unused because efficient redraw algorith hadn't implemented yet

/*
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
    checkPointX = (20*x+10) + GAME_CANVAS_START_X;
    checkPointY = (20*y+10) + GAME_CANVAS_START_Y;

    // Check current property on that block
    return is_inside_bitmap(gameParent->background, checkPointX, checkPointY, 0);
}
*/

void canvas::redrawBorder()
{

    blit(gameBorder, screen, 0, 0, 10, 10, 340, 460);
    blit(gameParent->background, screen, 20, 20, 20, 20, 320, 440);
}
