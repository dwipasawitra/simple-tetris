#include "game.h"

// Game abstract class implementation

void game::gameLoop()
{

    // Choose random new shape
    nextShapeType = rand() % 7;

    // OK now start the game loop
    while(!gameover)
    {
        // If KEY_DOWN pressed, then turbo the speed
        if(key[KEY_DOWN])
        {
            gameLoopSpeed = GAME_LOOP_SPEED_TURBO;
        }
        else
        {
            gameLoopSpeed = GAME_LOOP_SPEED_NORMAL;
        }

        // Step1: newShape from nextShapeType before
        if(gameState == GAME_STATE_NEWSHAPE_COMEOUT)
        {
            newShape(nextShapeType);
            nextShapeType = rand() % 7;
            gameState = GAME_STATE_NEWSHAPE_FALL;
        }
        // Step2: Full line deletion
        destroyLine();

        // Step3: Collision detector
        if(collideDetect())
        {
            setAllStoned();
            gameState = GAME_STATE_NEWSHAPE_COMEOUT;
        }
        else
        {
            // Step4: Get keyboard control command
            receiveControl();

            // Step5: Go down, flying thing
            goDown();

            // Step6: Redraw graphic
            redrawGraphic();
        }
        rest(gameLoopSpeed);

    }
}

void game::redrawGraphic()
{
    // Redraw algorithm
    // Check all matrix content
    // Check if there is a block there in graphic
    //
    // Yes: Keep it when matrix cell present
    //      Remove it when matrix cell doesn't present
    // No:  Draw it when matrix cell present
    //      Keep it when matrix cell doesn't present

    int i, j;

    // Iterator
    for(i=0;i<16;i++)
    {
        for(j=0;j<28;j++)
        {
            if(this->checkPoint(i, j)) if(this->gameBlock[i][j] != NULL) deleteBlock(i, j);
            else if(this->gameBlock[i][j] != NULL) drawBlock(i, j, &gameBlock[i][j]);
        }
    }
}

void game::drawBlock(int x, int y, block *property)
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
    drawPointY = (20*x + 10) + GAME_CANVAS_START_Y;

    // From center point, draw the 20x20 box;
    blockColor = property->blockColor;
    rectfill(screen, drawPointX-10, drawPointY-10, 20, 20, blockColor);

    // Done
}

void game::clearBlock(int x, int y)
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
    drawPointY = (20*x + 10) + GAME_CANVAS_START_Y;

    // From center point, clear its 20x20 box;
    rectfill(screen, drawPointX-10, drawPointY-10, 20, 20, GAME_CANVAS_BACKGROUND);

    // Done
}

bool game::checkPoint(int x, int y)
{
    int checkPointX, checkPointY;

    // If Y-axis is 0 to 3, you can't draw it
    if(y>=0 && y<=3)
    {
        return;
    }
    else
    {
        y = y-4;
    }

    // checkPoint = Center point of each block
    checkPointX = (20*x + 10) + GAME_CANVAS_START_X;
    checkPointY = (20*x + 10) + GAME_CANVAS_START_Y;

    // Check if there is something other than GAME_CANVAS_BACKGROUND in drawPoint
    if(getpixel(screen, checkPointX, checkPointY) == GAME_CANVAS_BACKGROUND) return 0;
    else return 1;
}

void game::newShape(int newShapeType)
{
    // Remember the new shape Type in Game Class
    this->newShapeType = newShapeType;

    // Get the shape new block color
    int newBlockColor = COLOR_BLUE;

    // Every new shape get 4 block, build the block first
    block *block1 = new block(newBlockColor, BLOCK_STATE_FLY);
    block *block2 = new block(newBlockColor, BLOCK_STATE_FLY);
    block *block3 = new block(newBlockColor, BLOCK_STATE_FLY);
    block *block4 = new block(newBlockColor, BLOCK_STATE_FLY);

    // First move point of new block;
    m = 8;
    n = 0;

    // OK, depending on its type, draw a new shape in Block
    switch(newShapeType)
    {
        case SHAPE_1A:
            // Block 1A:  Draw (m-1,n)(m,n)(m+1,n)(m+2,n)
            this->gameBlock[m-1][n] = block1;
            this->gameBlock[m][n] = block2;
            this->gameBlock[m+1][n] = block3;
            this->gameBlock[m+2][n] = block1;
            break;
        case SHAPE_1B:
            // Block 1B:  Draw (m,n-1)(m,n)(m,n+1)(m,n+2)
            this->gameBlock[m][n-1] = block1;
            this->gameBlock[m][n] = block2;
            this->gameBlock[m][n+1] = block3;
            this->gameBlock[m][n+2] = block4;
            break;
        case SHAPE_2A:
            // Block 2A:  Draw (m,n)(m+1,n)(m,n-1)(m+1,n+1)
            this->gameBlock[m][n] = block1;
            this->gameBlock[m+1][n] = block2;
            this->gameBlock[m][n-1] = block3;
            this->gameBlock[m+1][n+1] = block4;
            break;
        case SHAPE_2B:
            // Block 2B:  Draw (m,n)(m-1,n)(m,n+1)(m+1,n+1)
            this->gameBlock[m][n] = block1;
            this->gameBlock[m-1][n] = block2;
            this->gameBlock[m][n+1] = block3;
            this->gameBlock[m+1][n+1] = block4;
            break;
        case SHAPE_3A:
            // Block 3A:  Draw (m,n)(m,n+1)(m-1,n)(m-1,n-1)
            this->gameBlock[m][n] = block1;
            this->gameBlock[m][n+1] = block2;
            this->gameBlock[m-1][n] = block3;
            this->gameBlock[m-1][n-1] = block4;
            break;
        case SHAPE_3B:
            // Block 3B:  Draw (m,n)(m-1,n)(m,n-1)(m+1,n-1)
            this->gameBlock[m][n] = block1;
            this->gameBlock[m-1][n] = block2;
            this->gameBlock[m][n-1] = block3;
            this->gameBlock[m+1][n-1] = block4;
            break;
        case SHAPE_4:
            // Block 4:  Draw (m,n)(m,n+1)(m+1,n)(m+1,n+1)
            this->gameBlock[m][n] = block1;
            this->gameBlock[m][n+1] = block2;
            this->gameBlock[m+1][n] = block3;
            this->gameBlock[m+1][n+1] = block4;
            break;
    }

    // My job here is done
}

bool game::colideDetect()
{
    // Collide detect algorithm
    // NOTE: This is only detect collision between stoned block and flying block, not collision between
    // block and border of canvas (See game::goDown(), game::moveLeft() and game::moveRight() for more information)
    //
    // 1. Check newShapeType
    // 2. Depend on newShapeType, check lowest part of block (for each group by m, find highest n),
    //                            is there any block collide with BLOCK_STATE_STONED part
    // 3. If ok, return TRUE~

    switch(newShapeType)
    {
        case SHAPE_1A:
            // Block 1A Collision checker: (m-1,n)(m,n)(m+1,n)(m+2,n) a.k.a all 4 blocks
            if(gameBlock[m-1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameBlock[m][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameBlock[m+1[n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameBlock[m+2][n+1]->getState() == BLOCK_STATE_STONED) return true;
            break;
        case SHAPE_1B:
            // Block 1B Collision checker: Just (m,n+2).
            if(gameBlock[m][n+3]->getState() == BLOCK_STATE_STONED) return true;
            break;
        case SHAPE_2A:
            // Block 2A: Collision checker: (m,n)(m+1,n+1)
            if(gameBlock[m][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameBlock[m+1][n+2]->getState() == BLOCK_STATE_STONED) return true;
            break;
        case SHAPE_2B:
            // Block 2B: Collision checker: (m-1,n)(m,n+1)(m+1,n+1)
            if(gameBlock[m-1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameBlock[m][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(gameBlock[m+1][n+2]->getState() == BLOCK_STATE_STONED) return true;
            break;
        case SHAPE_3A:
            // Block 3A: Collision checker: (m,n+1)(m-1,n)
            if(gameBlock[m][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(gameBlock[m-1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            break;
        case SHAPE_3B:
            // Block 3B: Collision checker: (m,n)(m-1,n)(m+1,n-1)
            if(gameBlock[m][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameBlock[m-1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameBlock[m+1][n]->getState() == BLOCK_STATE_STONED) return true;
            break;
        case SHAPE_4:
            // Block 4: Collision checker: (m,n+1)(m+1,n+1)
            if(gameBlock[m][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(gameBlock[m+1][n+2]->getState() == BLOCK_STATE_STONED) return true;
            break;
    }

    return false;

    // That's not so hard, right?

}

void game::setAllStoned()
{
    // Check all gameBlocks matrix? Uhh.. no, that O(rows*cols) bro.
    // Just check newShapeType, than stoned some of them

    // Switch case problem bro
    switch(newShapeType)
    {
        case SHAPE_1A:
            // Block 1A:  Stoned (m-1,n)(m,n)(m+1,n)(m+2,n)
            this->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m+2][n]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_1B:
            // Block 1B:  Stoned (m,n-1)(m,n)(m,n+1)(m,n+2)
            this->gameBlock[m][n-1]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m][n+2]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_2A:
            // Block 2A:  Stoned (m,n)(m+1,n)(m,n-1)(m+1,n+1)
            this->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m][n-1]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m+1][n+1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_2B:
            // Block 2B:  Stoned (m,n)(m-1,n)(m,n+1)(m+1,n+1)
            this->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m+1][n+1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_3A:
            // Block 3A:  Stoned (m,n)(m,n+1)(m-1,n)(m-1,n-1)
            this->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m-1][n-1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_3B:
            // Block 3B:  Stoned (m,n)(m-1,n)(m,n-1)(m+1,n-1)
            this->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m][n-1]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m+1][n-1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_4:
            // Block 4:  Stoned (m,n)(m,n+1)(m+1,n)(m+1,n+1)
            this->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            this->gameBlock[m+1][n+1]->setState(BLOCK_STATE_STONED);
            break;
    }

    // Wow
}

void game::moveBlock(int x1, int y1, int x2, int y2)
{
    // Move block on [x1][y1] to [x2][y2] on this->gameBlock*[][] matrix
    block[x2][y2] = block[x1][y1];

    // Then remove [x1][y1] block
    block[x1][y1] = NULL;
}

void game::goDown()
{
    // Now the hardest part
    // But inefficient algorithm is inefficient, go check depend on newShapeType

    // Move the shape from lowest part (deepest n)


    switch(newShapeType)
    {
        case SHAPE_1A:
            // Block 1A:  Draw (m-1,n)(m,n)(m+1,n)(m+2,n)
            moveBlock(m-1,n,m-1,n+1);
            moveBlock(m,n,m,n+1);
            moveBlock(m+1,n,m+1,n+1);
            moveBlock(m+2,n,m+2,+1);
            break;
        case SHAPE_1B:
            // Block 1B:  Draw (m,n-1)(m,n)(m,n+1)(m,n+2)
            moveBlock(m,n+2,m,n+3);
            moveBlock(m,n+1,m,n+2);
            moveBlock(m,n,m,n+1);
            moveBlock(m,n-1,m,n);
            break;
        case SHAPE_2A:
            // Block 2A:  Draw (m,n)(m+1,n)(m,n-1)(m+1,n+1)
            moveBlock(m+1,n+1,m+1,n+2);
            moveBlock(m+1,n,m+1,n+1);
            moveBlock(m,n,m,n+1);
            moveBlock(m,n-1,m,n);
            break;
        case SHAPE_2B:
            // Block 2B:  Draw (m,n)(m-1,n)(m,n+1)(m+1,n+1)
            moveBlock(m,n+1,m,n+2);
            moveBlock(m+1,n+1,m+1,n+2);
            moveBlock(m-1,n,m-1,n+1);
            moveBlock(m,n,m,n+1);
            break;
        case SHAPE_3A:
            // Block 3A:  Draw (m,n)(m,n+1)(m-1,n)(m-1,n-1)
            moveBlock(m,n+1,m,n+2);
            moveBlock(m,n,m, n+1);
            moveBlock(m-1,n,m-1,n+1);
            moveBlock(m-1,n-1,m-1,n);
            break;
        case SHAPE_3B:
            // Block 3B:  Draw (m,n)(m-1,n)(m,n-1)(m+1,n-1)
            moveBlock(m,n,m,n+1);
            moveBlock(m-1,n,m-1,n+1);
            moveBlock(m,n-1,m,n);
            moveBlock(m+1,n-1,m+1,n);
            break;
        case SHAPE_4:
            // Block 4:  Draw (m,n)(m,n+1)(m+1,n)(m+1,n+1)
            moveBlock(m,n+1,m,n+2);
            moveBlock(m+1,n+1,m,n+2);
            moveBlock(m,n,m,n+1);
            moveBlock(m+1,n,m+1,n+1);
            break;
    }

    // Don't forget increment also n
    n++;

}

void game::moveLeft()
{
    switch(newShapeType)
    {
        case SHAPE_1A:
            // Block 1A:  Draw (m-1,n)(m,n)(m+1,n)(m+2,n)
            moveBlock(m-1,n,m-2,n);
            moveBlock(m,n,m-1,n);
            mo // KODING DARI SINI YA WIRA
            break;
        case SHAPE_1B:
            // Block 1B:  Draw (m,n-1)(m,n)(m,n+1)(m,n+2)
            moveBlock(m,n+2,m,n+3);
            moveBlock(m,n+1,m,n+2);
            moveBlock(m,n,m,n+1);
            moveBlock(m,n-1,m,n);
            break;
        case SHAPE_2A:
            // Block 2A:  Draw (m,n)(m+1,n)(m,n-1)(m+1,n+1)
            moveBlock(m+1,n+1,m+1,n+2);
            moveBlock(m+1,n,m+1,n+1);
            moveBlock(m,n,m,n+1);
            moveBlock(m,n-1,m,n);
            break;
        case SHAPE_2B:
            // Block 2B:  Draw (m,n)(m-1,n)(m,n+1)(m+1,n+1)
            moveBlock(m,n+1,m,n+2);
            moveBlock(m+1,n+1,m+1,n+2);
            moveBlock(m-1,n,m-1,n+1);
            moveBlock(m,n,m,n+1);
            break;
        case SHAPE_3A:
            // Block 3A:  Draw (m,n)(m,n+1)(m-1,n)(m-1,n-1)
            moveBlock(m,n+1,m,n+2);
            moveBlock(m,n,m, n+1);
            moveBlock(m-1,n,m-1,n+1);
            moveBlock(m-1,n-1,m-1,n);
            break;
        case SHAPE_3B:
            // Block 3B:  Draw (m,n)(m-1,n)(m,n-1)(m+1,n-1)
            moveBlock(m,n,m,n+1);
            moveBlock(m-1,n,m-1,n+1);
            moveBlock(m,n-1,m,n);
            moveBlock(m+1,n-1,m+1,n);
            break;
        case SHAPE_4:
            // Block 4:  Draw (m,n)(m,n+1)(m+1,n)(m+1,n+1)
            moveBlock(m,n+1,m,n+2);
            moveBlock(m+1,n+1,m,n+2);
            moveBlock(m,n,m,n+1);
            moveBlock(m+1,n,m+1,n+1);
            break;
    }

    // Don't forget increment also n
    m--;
}

void game::receiveKeystroke()
{

}

void game::moveLeft()
{

}
void game::moveRight()
{

}
void game::destroyLine()
{

}
void game::clearBlock()
{   int i, j;

    // Clear game matrix
    for(i=0;i<16;i++)
    {
        for(j=0;j<28<j++)
        {
            delete gameBlock[i][j];
            gameBlock[i][j] = NULL;
        }
    }
    rectfill(screen, 10, 0, 320, 480, makecol(170, 238, 255));
}
void game::newScore(string playerName)
{

}

// Interface Tetris class implementation
interfaceTetris::interfaceTetris()
{
    // First play, set game over to false
    gameover = false;
}

void interfaceTetris::newGame()
{
    // Clear the game screen
    this->clearBlock();

    // Start with new shape come out
    this->gameState = GAME_STATE_NEWSHAPE_COMEOUT;

    // OK, game loop starter until you are game over

    this->gameLoop();
}
void interfaceTetris::stopGame()
{

}
