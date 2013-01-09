#include "logic.h"

logic::logic(game *gameParent)
{
    this->gameParent = gameParent;
}

void logic::set_nextShapeType(int nextShapeType)
{
    this->nextShapeType = nextShapeType;
}


int logic::get_nextShapeType()
{
    return this->nextShapeType;
}

void logic::set_nextShapeColor(int nextShapeColor)
{
    this->nextShapeColor = nextShapeColor;
}

int logic::get_nextShapeColor()
{
    return this->nextShapeColor;
}

bool logic::gameLogicIteration()
{
    // If KEY_DOWN pressed, then turbo the speed
    gameParent->gameControl->receiveOnlyTurbo();

    // Step1: newShape from nextShapeType before
    if(this->gameState == GAME_STATE_NEWSHAPE_COMEOUT)
    {
        //cout << "Creating new shape" << endl;
        this->newShape(nextShapeType);

        this->nextShapeType = rand() % 18;
        //this->nextShapeType = SHAPE_7A;
        //cout << "Next shape is : " << nextShapeType << endl;
        this->gameState = GAME_STATE_NEWSHAPE_FALL;

        //cout << "Game state is GAME_STATE_NEWSHAPE_FALL" << endl;

    }
    // Step2: Full line deletion
    //cout << "Destroy line routine" << endl;
    this->destroyLine();

    //printMatrices();

    // Step3: Collision detector
    //cout << "Collision detector routine" << endl;
    if(this->collideDetect())
    {
        //cout << "Collision happened" << endl;
        this->setAllStoned();
        this->gameState = GAME_STATE_NEWSHAPE_COMEOUT;
    }
    else
    {
        //cout << "Collision didn't happened" << endl;

        // Step4: Get keyboard control command
        gameParent->gameControl->receiveControl();
        gameParent->gameCanvas->redrawGraphic();
         if(this->collideDetect())
        {
            //cek kedua
            this->setAllStoned();
            this->gameState = GAME_STATE_NEWSHAPE_COMEOUT;
        }
        else
            {

           // cout <<"2"<<endl;
            //gameParent->printMatrices();

            // Step5: Go down, flying thing
            this->goDown();

            // Step6: Redraw graphic
            gameParent->gameCanvas->redrawGraphic();
            }

    }
    rest(this->gameLoopSpeed);
    return false;

}



void logic::newShape(int newShapeType)
{
    // Remember the new shape Type in Game Class
    this->newShapeType = newShapeType;

    // Get the shape new block color
    int newBlockColor = rand() % 5;

    // Every new shape get 4 block, build the block first
    cout << "Creating 4 new block..." << endl;
    block *block1 = new block(newBlockColor, BLOCK_STATE_FLY);
    block *block2 = new block(newBlockColor, BLOCK_STATE_FLY);
    block *block3 = new block(newBlockColor, BLOCK_STATE_FLY);
    block *block4 = new block(newBlockColor, BLOCK_STATE_FLY);

    // First move point of new block;
    cout << "m=8, n=0" << endl;
    m = 8;
    n = 0;

    // OK, depending on its type, draw a new shape in Block
    switch(newShapeType)
    {
        case SHAPE_1A:
            // Block 1A:  Draw (m-1,n)(m,n)(m+1,n)(m+2,n)
            gameParent->gameBlock[m-1][n] = block1;
            gameParent->gameBlock[m][n] = block2;
            gameParent->gameBlock[m+1][n] = block3;
            gameParent->gameBlock[m+2][n] = block4;
            break;
        case SHAPE_1B:
            // Block 1B:  Draw (m,n-1)(m,n)(m,n+1)(m,n+2)
            gameParent->gameBlock[m][n-1] = block1;
            gameParent->gameBlock[m][n] = block2;
            gameParent->gameBlock[m][n+1] = block3;
            gameParent->gameBlock[m][n+2] = block4;
            break;
        case SHAPE_2A:
            // Block 2A:  Draw (m,n)(m+1,n)(m,n-1)(m+1,n+1)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m+1][n] = block2;
            gameParent->gameBlock[m][n-1] = block3;
            gameParent->gameBlock[m+1][n+1] = block4;
            break;
        case SHAPE_2B:
            // Block 2B:  Draw (m,n)(m-1,n)(m,n+1)(m+1,n+1)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m-1][n] = block2;
            gameParent->gameBlock[m][n+1] = block3;
            gameParent->gameBlock[m+1][n+1] = block4;
            break;
        case SHAPE_3A:
            // Block 3A:  Draw (m,n)(m,n+1)(m-1,n)(m-1,n-1)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m][n+1] = block2;
            gameParent->gameBlock[m+1][n] = block3;
            gameParent->gameBlock[m+1][n-1] = block4;
            break;
        case SHAPE_3B:
            // Block 3B:  Draw (m,n)(m-1,n)(m,n-1)(m+1,n-1)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m-1][n] = block2;
            gameParent->gameBlock[m][n-1] = block3;
            gameParent->gameBlock[m+1][n-1] = block4;
            break;
        case SHAPE_4:
            // Block 4:  Draw (m,n)(m,n+1)(m+1,n)(m+1,n+1)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m][n+1] = block2;
            gameParent->gameBlock[m+1][n] = block3;
            gameParent->gameBlock[m+1][n+1] = block4;
            break;
        case SHAPE_5A:
            // Block 5A: Draw (m,n) (m+1,n) (m-1,n) (m,n+1)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m+1][n] = block2;
            gameParent->gameBlock[m-1][n] = block3;
            gameParent->gameBlock[m][n+1] = block4;
            break;
        case SHAPE_5B:
            // Block 5B : Draw (m,n) (m+1,n) (m,n+1) (m,n-1)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m+1][n] = block2;
            gameParent->gameBlock[m][n+1] = block3;
            gameParent->gameBlock[m][n-1] = block4;
            break;
        case SHAPE_5C:
            // Block 5C : Draw (m,n) (m-1,n) (m,n+1) (m,n-1)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m-1][n] = block2;
            gameParent->gameBlock[m][n+1] = block3;
            gameParent->gameBlock[m][n-1] = block4;
            break;
        case SHAPE_5D:
            //Block 5D : Draw (m,n)(m-1,n) (m+1,n) (m,n-1)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m-1][n] = block2;
            gameParent->gameBlock[m+1][n] = block3;
            gameParent->gameBlock[m][n-1] = block4;
            break;
        case SHAPE_6A:
            //Block 6A :  Draw (m,n) (m+1,n) (m+2,n) (m,n-1)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m+1][n] = block2;
            gameParent->gameBlock[m+2][n] = block3;
            gameParent->gameBlock[m][n-1] = block4;
            break;
        case SHAPE_6B:
            //BLOCK 6B : Draw (m,n) (m+1,n) (m,n+1) (m,n+2)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m+1][n] = block2;
            gameParent->gameBlock[m][n+1] = block3;
            gameParent->gameBlock[m][n+2] = block4;
            break;
        case SHAPE_6C:
            //BLOCK 6C : Draw (m,n) (m-1,n) (m,n-1) (m,n-2)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m-1][n] = block2;
            gameParent->gameBlock[m][n-1] = block3;
            gameParent->gameBlock[m][n-2] = block4;
            break;
        case SHAPE_6D:
            //BLOCK 6D : Draw (m,n) (m-1,n) (m-2,n) (m,n+1)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m-1][n] = block2;
            gameParent->gameBlock[m-2][n] = block3;
            gameParent->gameBlock[m][n+1] = block4;
            break;
        case SHAPE_7A:
            //BLOCK 7A : Draw (m,n) (m,n-1) (m-1,n) (m-2,n)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m][n-1] = block2;
            gameParent->gameBlock[m-1][n] = block3;
            gameParent->gameBlock[m-2][n] = block4;
            break;
        case SHAPE_7B:
            //BLOCK 7B : Draw (m,n) (m-1,n) (m,n+1) (m,n+2)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m-1][n] = block2;
            gameParent->gameBlock[m][n+1] = block3;
            gameParent->gameBlock[m][n+2] = block4;
            break;
        case SHAPE_7C:
            //BLOCK 7C : Draw (m,n) (m+1,n) (m,n-1) (m,n-2)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m+1][n] = block2;
            gameParent->gameBlock[m][n-1] = block3;
            gameParent->gameBlock[m][n-2] = block4;
            break;
        case SHAPE_7D:
            //BLOCK 7D : Draw (m,n) (m+1,n) (m+2,n) (m,n+1)
            gameParent->gameBlock[m][n] = block1;
            gameParent->gameBlock[m+1][n] = block2;
            gameParent->gameBlock[m+2][n] = block3;
            gameParent->gameBlock[m][n+2] = block4;
            break;

    }

    // My job here is done
}

bool logic::collideDetect()
{
    // Collide detect algorithm
    // NOTE: This is only detect collision between stoned block and flying block, not collision between
    // block and border of canvas (See game::goDown(), game::moveLeft() and game::moveRight() for more information)
    //
    // 1. Check newShapeType
    // 2. Depend on newShapeType, check lowest part of block (for each group by m, find highest n),
    //                            is there any block collide with BLOCK_STATE_STONED part
    // 3. If ok, return TRUE~

    // PLIS CEK: Ketika shape kolid di pojok kanan bawah, program mengakses GameBlock pada bagian kolom diluar batas ukuran matrix
    switch(this->newShapeType)
    {
        case SHAPE_1A:
            // Block 1A Collision checker: (m-1,n)(m,n)(m+1,n)(m+2,n) a.k.a all 4 blocks

            if(gameParent->gameBlock[m-1][n+1]!=NULL)
                if(gameParent->gameBlock[m-1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m][n+1]!=NULL)
                if(gameParent->gameBlock[m][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+1][n+1]!=NULL)
                if(gameParent->gameBlock[m+1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+2][n+1]!=NULL)
                if(gameParent->gameBlock[m+2][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n == GAME_MAX_Y-1) return true;
            break;
        case SHAPE_1B:
            // Block 1B Collision checker: Just (m,n+2).
            if(gameParent->gameBlock[m][n+3]!=NULL)
                if(gameParent->gameBlock[m][n+3]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n+2 == GAME_MAX_Y-1) return true;
            break;
        case SHAPE_2A:
            // Block 2A: Collision checker: (m,n)(m+1,n+1)
            if(gameParent->gameBlock[m][n+1]!=NULL)
                if(gameParent->gameBlock[m][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+1][n+2]!=NULL)
                if(gameParent->gameBlock[m+1][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n+1 == GAME_MAX_Y-1) return true;
            break;
        case SHAPE_2B:
            // Block 2B: Collision checker: (m-1,n)(m,n+1)(m+1,n+1)
            if(gameParent->gameBlock[m-1][n+1]!=NULL)
                if(gameParent->gameBlock[m-1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m][n+2]!=NULL)
                if(gameParent->gameBlock[m][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+1][n+2]!=NULL)
                if(gameParent->gameBlock[m+1][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n+1 == GAME_MAX_Y-1) return true;
            break;
        case SHAPE_3A:
            // Block 3A: Collision checker: (m,n+1)(m-1,n)
            if(gameParent->gameBlock[m][n+2]!=NULL)
                if(gameParent->gameBlock[m][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+1][n+1]!=NULL)
                if(gameParent->gameBlock[m+1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n+1 == GAME_MAX_Y-1) return true;
            break;
        case SHAPE_3B:
            // Block 3B: Collision checker: (m,n)(m-1,n)(m+1,n-1)
            if(gameParent->gameBlock[m][n+1]!=NULL)
                if(gameParent->gameBlock[m][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m-1][n+1]!=NULL)
                if(gameParent->gameBlock[m-1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+1][n]!=NULL)
                if(gameParent->gameBlock[m+1][n]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n == GAME_MAX_Y-1) return true;
            break;
        case SHAPE_4:
            // Block 4: Collision checker: (m,n+1)(m+1,n+1)
            if(gameParent->gameBlock[m][n+2]!=NULL)
                if(gameParent->gameBlock[m][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+1][n+2]!=NULL)
                if(gameParent->gameBlock[m+1][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n+1 == GAME_MAX_Y-1) return true;
            break;
            case SHAPE_5A:
            // Block 5A: Collision checker: (m,n+2)(m+1,n+1) (m-1,n+1)
            if(gameParent->gameBlock[m][n+2]!=NULL)
                if(gameParent->gameBlock[m][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+1][n+1]!=NULL)
                if(gameParent->gameBlock[m+1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m-1][n+1]!=NULL)
                if(gameParent->gameBlock[m-1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n+1 == GAME_MAX_Y-1) return true;
            break;
            case SHAPE_5B:
            // Block 5A: Collision checker: (m,n+2)(m+1,n+1)
            if(gameParent->gameBlock[m][n+2]!=NULL)
                if(gameParent->gameBlock[m][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+1][n+1]!=NULL)
                if(gameParent->gameBlock[m+1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n+1 == GAME_MAX_Y-1) return true;
            break;
            case SHAPE_5C:
            // Block 5A: Collision checker: (m,n+2)(m-1,n+1)
            if(gameParent->gameBlock[m][n+2]!=NULL)
                if(gameParent->gameBlock[m][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m-1][n-1]!=NULL)
                if(gameParent->gameBlock[m+1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n+1 == GAME_MAX_Y-1) return true;
            break;
            case SHAPE_5D:
            // Block 5D: Collision checker: (m+1,n+1)(m,n+1) (m-1,n+1)
            if(gameParent->gameBlock[m+1][n+1]!=NULL)
                if(gameParent->gameBlock[m+1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m][n+1]!=NULL)
                if(gameParent->gameBlock[m][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m-1][n+1]!=NULL)
                if(gameParent->gameBlock[m-1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n == GAME_MAX_Y-1) return true;
            break;
            case SHAPE_6A:
            // Block 6A: Collision checker: (m,n+1)(m+1,n+1) (m+2,n+1)
            if(gameParent->gameBlock[m][n+1]!=NULL)
                if(gameParent->gameBlock[m][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+1][n+1]!=NULL)
                if(gameParent->gameBlock[m+1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+2][n+1]!=NULL)
                if(gameParent->gameBlock[m+2][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n == GAME_MAX_Y-1) return true;
            break;
            case SHAPE_6B:
            // Block 6B: Collision checker: (m,n+3)(m+1,n+1)
            if(gameParent->gameBlock[m][n+3]!=NULL)
                if(gameParent->gameBlock[m][n+3]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+1][n+1]!=NULL)
                if(gameParent->gameBlock[m+1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n+2 == GAME_MAX_Y-1) return true;
            break;
            case SHAPE_6C:
            // Block 6C: Collision checker: (m-1,n+1)(m,n+1)
            if(gameParent->gameBlock[m-1][n+1]!=NULL)
                if(gameParent->gameBlock[m-1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m][n+1]!=NULL)
                if(gameParent->gameBlock[m][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n == GAME_MAX_Y-1) return true;
            break;
            case SHAPE_6D:
            // Block 6D: Collision checker: (m,n+2)(m-1,n+1) (m-2,n+1)
            if(gameParent->gameBlock[m][n+2]!=NULL)
                if(gameParent->gameBlock[m][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m-1][n+1]!=NULL)
                if(gameParent->gameBlock[m-1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m-2][n+1]!=NULL)
                if(gameParent->gameBlock[m-2][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n+1 == GAME_MAX_Y-1) return true;
            break;
            case SHAPE_7A:
            // Block 7A: Collision checker: (m,n+1)(m-1,n+1) (m-2,n+1)
            if(gameParent->gameBlock[m][n+1]!=NULL)
                if(gameParent->gameBlock[m][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m-1][n+1]!=NULL)
                if(gameParent->gameBlock[m-1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m-2][n+1]!=NULL)
                if(gameParent->gameBlock[m-2][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n == GAME_MAX_Y-1) return true;
            break;
            case SHAPE_7B:
            // Block 7B: Collision checker: (m,n+3)(m-1,n+1)
            if(gameParent->gameBlock[m][n+3]!=NULL)
                if(gameParent->gameBlock[m][n+3]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m-1][n+1]!=NULL)
                if(gameParent->gameBlock[m-1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n+2 == GAME_MAX_Y-1) return true;
            break;
            case SHAPE_7C:
            // Block 7C: Collision checker: (m,n+1)(m+1,n+1)
            if(gameParent->gameBlock[m][n+1]!=NULL)
                if(gameParent->gameBlock[m][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+1][n+1]!=NULL)
                if(gameParent->gameBlock[m+1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n == GAME_MAX_Y-1) return true;
            break;
            case SHAPE_7D:
            // Block 7D: Collision checker: (m,n+2)(m+1,n+1) (m+2,n+1)
            if(gameParent->gameBlock[m][n+2]!=NULL)
                if(gameParent->gameBlock[m][n+2]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+1][n+1]!=NULL)
                if(gameParent->gameBlock[m+1][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(gameParent->gameBlock[m+2][n+1]!=NULL)
                if(gameParent->gameBlock[m+2][n+1]->getState() == BLOCK_STATE_STONED) return true;
            if(this->n+1 == GAME_MAX_Y-1) return true;
            break;
    }



    return false;

    // That's not so hard, right?

}

void logic::setAllStoned()
{
    // Check all gameBlocks matrix? Uhh.. no, that O(rows*cols) bro.
    // Just check newShapeType, than stoned some of them

    // Switch case problem bro
    switch(this->newShapeType)
    {
        case SHAPE_1A:
            // Block 1A:  Stoned (m-1,n)(m,n)(m+1,n)(m+2,n)
            gameParent->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+2][n]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_1B:
            // Block 1B:  Stoned (m,n-1)(m,n)(m,n+1)(m,n+2)
            gameParent->gameBlock[m][n-1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+2]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_2A:
            // Block 2A:  Stoned (m,n)(m+1,n)(m,n-1)(m+1,n+1)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n-1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n+1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_2B:
            // Block 2B:  Stoned (m,n)(m-1,n)(m,n+1)(m+1,n+1)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n+1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_3A:
            // Block 3A:  Stoned (m,n)(m,n+1)(m-1,n)(m-1,n-1)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n-1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_3B:
            // Block 3B:  Stoned (m,n)(m-1,n)(m,n-1)(m+1,n-1)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n-1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n-1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_4:
            // Block 4:  Stoned (m,n)(m,n+1)(m+1,n)(m+1,n+1)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n+1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_5A:
            // Block 5A: Draw (m,n) (m+1,n) (m-1,n) (m,n+1)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_5B:
            // Block 5B : Draw (m,n) (m+1,n) (m,n+1) (m,n-1)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n-1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_5C:
            // Block 5C : Draw (m,n) (m-1,n) (m,n+1) (m,n-1)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n-1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_5D:
            //Block 5D : Draw (m,n)(m-1,n) (m+1,n) (m,n-1)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n-1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_6A:
            //Block 6A :  Draw (m,n) (m+1,n) (m+2,n) (m,n-1)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+2][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n-1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_6B:
            //BLOCK 6B : Draw (m,n) (m+1,n) (m,n+1) (m,n+2)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+2]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_6C:
            //BLOCK 6C : Draw (m,n) (m-1,n) (m,n-1) (m,n-2)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n-1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n-2]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_6D:
            //BLOCK 6D : Draw (m,n) (m-1,n) (m-2,n) (m,n+1)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m-2][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_7A:
            //BLOCK 7A : Draw (m,n) (m,n-1) (m-1,n) (m-2,n)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n-1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m-2][n]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_7B:
            //BLOCK 7B : Draw (m,n) (m-1,n) (m,n+1) (m,n+2)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m-1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+2]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_7C:
            //BLOCK 7C : Draw (m,n) (m+1,n) (m,n-1) (m,n-2)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n-1]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n-2]->setState(BLOCK_STATE_STONED);
            break;
        case SHAPE_7D:
            //BLOCK 7D : Draw (m,n) (m+1,n) (m+2,n) (m,n+1)
            gameParent->gameBlock[m][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+1][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m+2][n]->setState(BLOCK_STATE_STONED);
            gameParent->gameBlock[m][n+2]->setState(BLOCK_STATE_STONED);
            break;
    }

    //cout << "Shape stoned" << endl;
    // Wow
}

void logic::moveBlock(int x1, int y1, int x2, int y2)
{
    // Move block on [x1][y1] to [x2][y2] on this->gameBlock*[][] matrix
    gameParent->gameBlock[x2][y2] = gameParent->gameBlock[x1][y1];

    // Then remove [x1][y1] block
    gameParent->gameBlock[x1][y1] = NULL;
}

void logic::goDown()
{
    // Now the hardest part
    // But inefficient algorithm is inefficient, go check depend on newShapeType

    // Move the shape from lowest part (deepest n)


    switch(this->newShapeType)
    {
        case SHAPE_1A:
            // Block 1A:  Draw (m-1,n)(m,n)(m+1,n)(m+2,n)
            if(this->n < GAME_MAX_Y - 1)
            {
                this->moveBlock(m-1,n,m-1,n+1);
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m+1,n,m+1,n+1);
                this->moveBlock(m+2,n,m+2,n+1);
            }
            break;
        case SHAPE_1B:
            // Block 1B:  Draw (m,n-1)(m,n)(m,n+1)(m,n+2)
            if(this->n+2 < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n+2,m,n+3);
                this->moveBlock(m,n+1,m,n+2);
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m,n-1,m,n);
            }
            break;
        case SHAPE_2A:
            // Block 2A:  Draw (m,n)(m+1,n)(m,n-1)(m+1,n+1)
            if(this->n+1 < GAME_MAX_Y - 1)
            {
                this->moveBlock(m+1,n+1,m+1,n+2);
                this->moveBlock(m+1,n,m+1,n+1);
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m,n-1,m,n);
            }
            break;
        case SHAPE_2B:
            // Block 2B:  Draw (m,n)(m-1,n)(m,n+1)(m+1,n+1)
            if(this->n+1 < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n+1,m,n+2);
                this->moveBlock(m+1,n+1,m+1,n+2);
                this->moveBlock(m-1,n,m-1,n+1);
                this->moveBlock(m,n,m,n+1);
            }
            break;
        case SHAPE_3A:
            // Block 3A:  Draw (m,n)(m,n+1)(m-1,n)(m-1,n-1)
            if(this->n < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n+1,m,n+2);
                this->moveBlock(m,n,m, n+1);
                this->moveBlock(m+1,n,m+1,n+1);
                this->moveBlock(m+1,n-1,m+1,n);
            }
            break;
        case SHAPE_3B:
            // Block 3B:  Draw (m,n)(m-1,n)(m,n-1)(m+1,n-1)
            if(this->n < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m-1,n,m-1,n+1);
                this->moveBlock(m,n-1,m,n);
                this->moveBlock(m+1,n-1,m+1,n);
            }
            break;
        case SHAPE_4:
            // Block 4:  Draw (m,n)(m,n+1)(m+1,n)(m+1,n+1)
            if(this->n+1 < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n+1,m,n+2);
                this->moveBlock(m+1,n+1,m+1,n+2);
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m+1,n,m+1,n+1);
            }
            break;
        case SHAPE_5A:
            // Block 5A:  Draw (m,n+1)(m,n)(m+1,n)(m-1,n)
            if(this->n+1 < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n+1,m,n+2);
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m+1,n,m+1,n+1);
                this->moveBlock(m-1,n,m-1,n+1);
            }
            break;
        case SHAPE_5B:
            // Block 5B:  Draw (m,n+1)(m,n)(m,n-1)(m+1,n)
            if(this->n+1 < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n+1,m,n+2);
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m,n-1,m,n);
                this->moveBlock(m+1,n,m+1,n+1);
            }
            break;
        case SHAPE_5C:
            // Block 5C:  Draw (m,n+1)(m,n)(m,n-1)(m-1,n)
            if(this->n+1 < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n+1,m,n+2);
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m,n-1,m,n);
                this->moveBlock(m-1,n,m-1,n+1);
            }
            break;
        case SHAPE_5D:
            // Block 5C:  Draw (m,n)(m,n+1)(m+1,n)(m-1,n)
            if(this->n < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m,n-1,m,n);
                this->moveBlock(m+1,n,m+1,n+1);
                this->moveBlock(m-1,n,m-1,n+1);
            }
            break;
        case SHAPE_6A:
            // Block 6B:  Draw (m,n)(m,n-1)(m+1,n)(m+2,n)
            if(this->n < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m,n-1,m,n);
                this->moveBlock(m+1,n,m+1,n+1);
                this->moveBlock(m+2,n,m+2,n+1);
            }
            break;
        case SHAPE_6B:
            // Block 6B:  Draw (m,n+2)(m,n+1)(m+1,n)(m,n)
            if(this->n+2 < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n+2,m,n+3);
                this->moveBlock(m,n+1,m,n+2);
                this->moveBlock(m+1,n,m+1,n+1);
                this->moveBlock(m,n,m,n+1);
            }
            break;
        case SHAPE_6C:
            // Block 6C:  Draw (m,n)(m,n+1)(m,n+2)(m-1,n)
            if(this->n < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m,n-1,m,n);
                this->moveBlock(m,n-2,m,n-1);
                this->moveBlock(m-1,n,m-1,n+1);
            }
            break;
        case SHAPE_6D:
            // Block 6D:  Draw (m,n+1)(m,n)(m+1,n)(m+2,n)
            if(this->n+1 < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n+1,m,n+2);
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m-1,n,m-1,n+1);
                this->moveBlock(m-2,n,m-2,n+1);
            }
            break;
        case SHAPE_7A:
            // Block 7A:  Draw (m,n)(m,n-1)(m-2,n)(m-1,n)
            if(this->n < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m,n-1,m,n);
                this->moveBlock(m-2,n,m-2,n+1);
                this->moveBlock(m-1,n,m-1,n+1);
            }
            break;
        case SHAPE_7B:
            // Block 7B:  Draw (m,n+2)(m,n+1)(m-1,n)(m,n)
            if(this->n+2 < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n+2,m,n+3);
                this->moveBlock(m,n+1,m,n+2);
                this->moveBlock(m-1,n,m-1,n+1);
                this->moveBlock(m,n,m,n+1);
            }
            break;
        case SHAPE_7C:
            // Block 7C:  Draw (m,n)(m,n-1)(m,n-2)(m+1,n)
            if(this->n < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m,n-1,m,n);
                this->moveBlock(m,n-2,m,n-1);
                this->moveBlock(m+1,n,m+1,n+1);
            }
            break;
        case SHAPE_7D:
            // Block 7D:  Draw (m,n+1)(m,n)(m+1,n)(m+2,n)
            if(this->n+1 < GAME_MAX_Y - 1)
            {
                this->moveBlock(m,n+1,m,n+2);
                this->moveBlock(m,n,m,n+1);
                this->moveBlock(m+1,n,m+1,n+1);
                this->moveBlock(m+2,n,m+2,n+1);
            }
            break;
    }

    // Don't forget increment also n
    if(this->n < GAME_MAX_Y - 1) this->n++;

}

void logic::moveLeft()
{
    // Same as goDown()
    // But do the move ONLY if the leftest part of shape doesn't collide with game canvas border
    // PLIS CEK: Ketika shape dibawa ke kiri, shape tidak melihat adanya shape (hanya melihat batas kanvas)

    switch(this->newShapeType)
    {
        case SHAPE_1A:
            // Block 1A:  Draw (m-1,n)(m,n)(m+1,n)(m+2,n)
            if(this->m-1 > 0)
            {
                if(gameParent->gameBlock[m-2][n]==NULL)
                {
                    this->moveBlock(m-1,n,m-2,n);
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m+1,n,m,n);
                    this->moveBlock(m+2,n,m+1,n);
                    this->m--;
                }
            }
            break;
        case SHAPE_1B:
            // Block 1B:  Draw (m,n-1)(m,n)(m,n+1)(m,n+2)
            if(this->m > 0)
            {
                if(gameParent->gameBlock[m-1][n]==NULL && gameParent->gameBlock[m-1][n-1]==NULL && gameParent->gameBlock[m-1][n+1]==NULL && gameParent->gameBlock[m-1][n+2]==NULL)
                {
                    this->moveBlock(m,n-1,m-1,n-1);
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m,n+1,m-1,n+1);
                    this->moveBlock(m,n+2,m-1,n+2);
                    this->m--;
                }
            }
            break;
        case SHAPE_2A:
            // Block 2A:  Draw (m,n)(m+1,n)(m,n-1)(m+1,n+1)
            if(this->m > 0)
            {
                if(gameParent->gameBlock[m-1][n]==NULL && gameParent->gameBlock[m-1][n-1]==NULL && gameParent->gameBlock[m][n+1]==NULL)
                {
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m,n-1,m-1,n-1);
                    this->moveBlock(m+1,n,m,n);
                    this->moveBlock(m+1,n+1,m,n+1);
                    this->m--;
                }
            }
            break;
        case SHAPE_2B:
            // Block 2B:  Draw (m,n)(m-1,n)(m,n+1)(m+1,n+1)
            if(this->m-1 > 0)
            {
                if(gameParent->gameBlock[m-2][n]==NULL && gameParent->gameBlock[m-1][n+1]==NULL)
                {
                    this->moveBlock(m-1,n,m-2,n);
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m,n+1,m-1,n+1);
                    this->moveBlock(m+1,n+1,m,n+1);
                    this->m--;
                }
            }
            break;
        case SHAPE_3A:
            // Block 3A:  Draw (m,n)(m,n+1)(m-1,n)(m-1,n-1)
            if(this->m-1 > 0)
            {
                if(gameParent->gameBlock[m-1][n]==NULL && gameParent->gameBlock[m-1][n+1]==NULL && gameParent->gameBlock[m][n-1]==NULL)
                {
                    this->moveBlock(m,n+1,m-1,n+1);
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m+1,n,m,n);
                    this->moveBlock(m+1,n-1,m,n-1);
                    this->m--;
                }
            }
            break;
        case SHAPE_3B:
            // Block 3B:  Draw (m,n)(m-1,n)(m,n-1)(m+1,n-1)
            if(this->m-1 > 0)
            {
                if(gameParent->gameBlock[m-2][n]==NULL && gameParent->gameBlock[m-1][n-1]==NULL )
                {
                    this->moveBlock(m-1,n,m-2,n);
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m,n-1,m-1,n-1);
                    this->moveBlock(m+1,n-1,m,n-1);
                    this->m--;
                }
            }
            break;
        case SHAPE_4:
            // Block 4:  Draw (m,n)(m,n+1)(m+1,n)(m+1,n+1)
            if(this->m > 0)
            {
                if(gameParent->gameBlock[m-1][n]==NULL && gameParent->gameBlock[m-1][n+1]==NULL)
                {
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m,n+1,m-1,n+1);
                    this->moveBlock(m+1,n,m,n);
                    this->moveBlock(m+1,n+1,m,n+1);
                    this->m--;
                }
            }
            break;
        case SHAPE_5A:
            // Block 5A:  Draw (m-1,n)(m,n)(m+1,n)(m,n+1)
            if(this->m-1> 0)
            {
                if(gameParent->gameBlock[m-2][n]==NULL && gameParent->gameBlock[m-1][n+1]==NULL)
                {
                    this->moveBlock(m-1,n,m-2,n);
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m+1,n,m,n);
                    this->moveBlock(m,n+1,m-1,n+1);
                    this->m--;
                }
            }
            break;
        case SHAPE_5B:
            // Block 5B:  Draw (m,n)(m+1,n)(m,n-1)(m,n+1)
            if(this->m > 0)
            {
                if(gameParent->gameBlock[m-1][n]==NULL && gameParent->gameBlock[m-1][n+1]==NULL && gameParent->gameBlock[m-1][n-1]==NULL)
                {
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m+1,n,m,n);
                    this->moveBlock(m,n-1,m-1,n-1);
                    this->moveBlock(m,n+1,m-1,n+1);
                    this->m--;
                }
            }
            break;
        case SHAPE_5C:
            // Block 5C:  Draw (m-1,n)(m,n)(m,n-1)(m,n+1)
            if(this->m-1 > 0)
            {
                if(gameParent->gameBlock[m-2][n]==NULL && gameParent->gameBlock[m-1][n+1]==NULL && gameParent->gameBlock[m-1][n-1]==NULL && gameParent->gameBlock[m-1][n+2]==NULL)
                {
                    this->moveBlock(m-1,n,m-2,n);
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m,n-1,m-1,n-1);
                    this->moveBlock(m,n+1,m-1,n+1);
                    this->m--;
                }
            }
            break;
        case SHAPE_5D:
            // Block 5D:  Draw (m-1,n)(m,n)(m+1,n)(m,n-1)
            if(this->m > 0)
            {
                if(gameParent->gameBlock[m-2][n]==NULL && gameParent->gameBlock[m-1][n-1]==NULL)
                {
                    this->moveBlock(m-1,n,m-2,n);
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m+1,n,m,n);
                    this->moveBlock(m,n-1,m-1,n-1);
                    this->m--;
                }
            }
            break;
        case SHAPE_6A:
            // Block 6A:  Draw (m,n)(m+1,n)(m+2,n)(m,n+1)
            if(this->m > 0)
            {
                if(gameParent->gameBlock[m-1][n]==NULL && gameParent->gameBlock[m-1][n-1]==NULL)
                {
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m+1,n,m,n);
                    this->moveBlock(m+2,n,m+1,n);
                    this->moveBlock(m,n-1,m-1,n-1);
                    this->m--;
                }
            }
            break;
        case SHAPE_6B:
            // Block 6A:  Draw (m,n)(m+1,n)(m,n+2)(m,n+1)
            if(this->m > 0)
            {
                if(gameParent->gameBlock[m-1][n]==NULL && gameParent->gameBlock[m-1][n+1]==NULL && gameParent->gameBlock[m-1][n+2]==NULL)
                {
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m+1,n,m,n);
                    this->moveBlock(m,n+2,m-1,n+2);
                    this->moveBlock(m,n+1,m-1,n+1);
                    this->m--;
                }
            }
            break;
        case SHAPE_6C:
            // Block 6C:  Draw (m-1,n)(m,n)(m,n-2)(m,n-1)
            if(this->m-1 > 0)
            {
                if(gameParent->gameBlock[m-2][n]==NULL && gameParent->gameBlock[m-1][n-1]==NULL && gameParent->gameBlock[m-1][n-2]==NULL)
                {
                    this->moveBlock(m-1,n,m-2,n);
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m,n-2,m-1,n-2);
                    this->moveBlock(m,n-1,m-1,n-1);
                    this->m--;
                }
            }
            break;
        case SHAPE_6D:
            // Block 6D:  Draw (m-2,n)(m-1,n)(m,n)(m,n+1)
            if(this->m-2 > 0)
            {
                if(gameParent->gameBlock[m-3][n]==NULL && gameParent->gameBlock[m-1][n+1]==NULL )
                {
                    this->moveBlock(m-2,n,m-3,n);
                    this->moveBlock(m-1,n,m-2,n);
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m,n+1,m-1,n+1);
                    this->m--;
                }
            }
            break;
        case SHAPE_7A:
            // Block 6A:  Draw (m-2,n)(m-1,n)(m,n)(m,n+1)
            if(this->m-2 > 0)
            {
                if(gameParent->gameBlock[m-3][n]==NULL && gameParent->gameBlock[m-1][n-1]==NULL)
                {
                    this->moveBlock(m-2,n,m-3,n);
                    this->moveBlock(m-1,n,m-2,n);
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m,n-1,m-1,n-1);
                    this->m--;
                }
            }
            break;
        case SHAPE_7B:
            // Block 7B:  Draw (m-1,n)(m,n)(m,n+2)(m,n+1)
            if(this->m-1 > 0)
            {
                if(gameParent->gameBlock[m-2][n]==NULL && gameParent->gameBlock[m-1][n+1]==NULL && gameParent->gameBlock[m-1][n+2]==NULL)
                {
                    this->moveBlock(m-1,n,m-2,n);
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m,n+2,m-1,n+2);
                    this->moveBlock(m,n+1,m-1,n+1);
                    this->m--;
                }
            }
            break;
        case SHAPE_7C:
            // Block 7C:  Draw (m,n)(m-1,n)(m,n-2)(m,n-1)
            if(this->m > 0)
            {
                if(gameParent->gameBlock[m-1][n]==NULL && gameParent->gameBlock[m-1][n-1]==NULL && gameParent->gameBlock[m-1][n-2]==NULL)
                {
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m+1,n,m,n);
                    this->moveBlock(m,n-2,m-1,n-2);
                    this->moveBlock(m,n-1,m-1,n-1);
                    this->m--;
                }
            }
            break;
        case SHAPE_7D:
            // Block 7D:  Draw (m,n)(m+1,n)(m+2,n)(m,n+1)
            if(this->m > 0)
            {
                if(gameParent->gameBlock[m-1][n]==NULL && gameParent->gameBlock[m-1][n+1]==NULL )
                {
                    this->moveBlock(m,n,m-1,n);
                    this->moveBlock(m+1,n,m,n);
                    this->moveBlock(m+2,n,m+1,n);
                    this->moveBlock(m,n+1,m-1,n+1);
                    this->m--;
                }
            }
            break;
    }

}

void logic::moveRight()
{
    // Same as goDown()
    // But do the move ONLY if the leftest part of shape doesn't collide with game canvas border
    // PLIS CEK: Ketika shape dibawa ke kanan, shape tidak melihat adanya shape (hanya melihat batas kanvas)

    switch(this->newShapeType)
    {
        case SHAPE_1A:
            // Block 1A:  Draw (m-1,n)(m,n)(m+1,n)(m+2,n)
            if(this->m+2 < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+3][n]==NULL)
                {
                    this->moveBlock(m+2,n,m+3,n);
                    this->moveBlock(m+1,n,m+2,n);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m-1,n,m,n);
                    m++;
                }
            }
            break;
        case SHAPE_1B:
            // Block 1B:  Draw (m,n-1)(m,n)(m,n+1)(m,n+2)
            if(this->m < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+1][n]==NULL && gameParent->gameBlock[m+1][n-1]==NULL && gameParent->gameBlock[m+1][n+1]==NULL && gameParent->gameBlock[m+1][n+2]==NULL)
                {
                    this->moveBlock(m,n-1,m+1,n-1);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m,n+1,m+1,n+1);
                    this->moveBlock(m,n+2,m+1,n+2);
                    this->m++;
                }
            }
            break;
        case SHAPE_2A:
            // Block 2A:  Draw (m,n)(m+1,n)(m,n-1)(m+1,n+1)
            if(this->m+1 < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+2][n]==NULL && gameParent->gameBlock[m+2][n+1]==NULL && gameParent->gameBlock[m+1][n-1]==NULL)
                {
                    this->moveBlock(m+1,n,m+2,n);
                    this->moveBlock(m+1,n+1,m+2,n+1);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m,n-1,m+1,n-1);
                    this->m++;
                }
            }
            break;
        case SHAPE_2B:
            // Block 2B:  Draw (m,n)(m-1,n)(m,n+1)(m+1,n+1)
            if(this->m+1 < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+1][n]==NULL && gameParent->gameBlock[m+2][n+1]==NULL)
                {
                    this->moveBlock(m+1,n+1,m+2,n+1);
                    this->moveBlock(m,n+1,m+1,n+1);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m-1,n,m,n);
                    this->m++;
                }
            }
            break;
        case SHAPE_3A:
            // Block 3A:  Draw (m,n)(m,n+1)(m-1,n)(m-1,n-1)
            if(this->m+1 < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+2][n]==NULL && gameParent->gameBlock[m+2][n-1]==NULL && gameParent->gameBlock[m+1][n+1]==NULL)
                {
                    this->moveBlock(m+1,n-1,m+2,n-1);
                    this->moveBlock(m+1,n,m+2,n);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m,n+1,m+1,n+1);
                    this->m++;
                }
            }
            break;
        case SHAPE_3B:
            // Block 3B:  Draw (m,n)(m-1,n)(m,n-1)(m+1,n-1)
            if(this->m+1 < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+1][n]==NULL && gameParent->gameBlock[m+2][n-1]==NULL)
                {
                    this->moveBlock(m+1,n-1,m+2,n-1);
                    this->moveBlock(m,n-1,m+1,n-1);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m-1,n,m,n);
                    this->m++;
                }
            }
            break;
        case SHAPE_4:
            // Block 4:  Draw (m,n)(m,n+1)(m+1,n)(m+1,n+1)
            if(this->m+1 < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+2][n]==NULL && gameParent->gameBlock[m+2][n+1]==NULL)
                {
                    this->moveBlock(m+1,n,m+2,n);
                    this->moveBlock(m+1,n+1,m+2,n+1);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m,n+1,m+1,n+1);
                    this->m++;
                }
            }
            break;
        case SHAPE_5A:
            // Block 5A:  Draw (m+1,n)(m,n)(m-1,n)(m,n+1)
            if(this->m+1 < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+2][n]==NULL && gameParent->gameBlock[m+1][n+1]==NULL)
                {
                    this->moveBlock(m+1,n,m+2,n);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m-1,n,m,n);
                    this->moveBlock(m,n+1,m+1,n+1);
                    m++;
                }
            }
            break;
        case SHAPE_5B:
            // Block 5B:  Draw (m+1,n)(m,n)(m,n-1)(m,n+1)
            if(this->m+1 < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+2][n]==NULL && gameParent->gameBlock[m+1][n+1]==NULL && gameParent->gameBlock[m+1][n-1]==NULL)
                {
                    this->moveBlock(m+1,n,m+2,n);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m,n-1,m+1,n-1);
                    this->moveBlock(m,n+1,m+1,n+1);
                    m++;
                }
            }
            break;
        case SHAPE_5C:
            // Block 5C:  Draw (m,n)(m-1,n)(m,n-1)(m,n+1)
            if(this->m < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+1][n]==NULL && gameParent->gameBlock[m+1][n+1]==NULL && gameParent->gameBlock[m+1][n-1]==NULL)
                {
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m-1,n,m,n);
                    this->moveBlock(m,n-1,m+1,n-1);
                    this->moveBlock(m,n+1,m+1,n+1);
                    m++;
                }
            }
            break;
        case SHAPE_5D:
            // Block 5D:  Draw (m+1,n)(m,n)(m-1,n)(m,n-1)
            if(this->m+1 < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+2][n]==NULL && gameParent->gameBlock[m+1][n-1]==NULL )
                {
                    this->moveBlock(m+1,n,m+2,n);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m-1,n,m,n);
                    this->moveBlock(m,n-1,m+1,n-1);
                    m++;
                }
            }
            break;
        case SHAPE_6A:
            // Block 6A:  Draw (m+2,n)(m+1,n)(m,n)(m,n-1)
            if(this->m+2 < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+3][n]==NULL && gameParent->gameBlock[m+1][n-1]==NULL )
                {
                    this->moveBlock(m+2,n,m+3,n);
                    this->moveBlock(m+1,n,m+2,n);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m,n-1,m+1,n-1);
                    m++;
                }
            }
            break;
        case SHAPE_6B:
            // Block 6A:  Draw (m+1,n)(m,n)(m,n+1)(m,n+2)
            if(this->m+1 < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+2][n]==NULL && gameParent->gameBlock[m+1][n+1]==NULL && gameParent->gameBlock[m+2][n+1]==NULL)
                {
                    this->moveBlock(m+1,n,m+2,n);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m,n+1,m+1,n+1);
                    this->moveBlock(m,n+2,m+1,n+2);
                    m++;
                }
            }
            break;
        case SHAPE_6C:
            // Block 6C:  Draw (m,n)(m-1,n)(m,n+1)(m,n+2)
            if(this->m < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+1][n]==NULL && gameParent->gameBlock[m+1][n+1]==NULL && gameParent->gameBlock[m+2][n+1]==NULL)
                {
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m-1,n,m,n);
                    this->moveBlock(m,n-1,m+1,n-1);
                    this->moveBlock(m,n-2,m+1,n-2);
                    m++;
                }
            }
            break;
        case SHAPE_6D:
            // Block 6D:  Draw (m,n)(m-1,n)(m-2,n)(m,n+1)
            if(this->m < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+1][n]==NULL && gameParent->gameBlock[m+1][n+1]==NULL)
                {
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m-1,n,m,n);
                    this->moveBlock(m-2,n,m-1,n);
                    this->moveBlock(m,n+1,m+1,n+1);
                    m++;
                }
            }
            break;
        case SHAPE_7A:
            // Block 7A:  Draw (m,n)(m-1,n)(m-2,n)(m,n-1)
            if(this->m < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+1][n]==NULL && gameParent->gameBlock[m+1][n-1]==NULL )
                {
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m-1,n,m,n);
                    this->moveBlock(m-2,n,m-1,n);
                    this->moveBlock(m,n-1,m+1,n-1);
                    m++;
                }
            }
            break;
        case SHAPE_7B:
            // Block 7B:  Draw (m,n)(m-1,n)(m,n+1)(m,n+2)
            if(this->m < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+1][n]==NULL && gameParent->gameBlock[m+1][n+1]==NULL && gameParent->gameBlock[m+2][n+1]==NULL)
                {
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m-1,n,m,n);
                    this->moveBlock(m,n+1,m+1,n+1);
                    this->moveBlock(m,n+2,m+1,n+2);
                    m++;
                }
            }
            break;
        case SHAPE_7C:
            // Block 7C:  Draw (m+1,n)(m,n)(m,n+1)(m,n+2)
            if(this->m+2 < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+2][n]==NULL && gameParent->gameBlock[m+1][n+1]==NULL && gameParent->gameBlock[m+2][n+1]==NULL)
                {
                    this->moveBlock(m+1,n,m+2,n);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m,n-1,m+1,n-1);
                    this->moveBlock(m,n-2,m+1,n-2);
                    m++;
                }
            }
            break;
        case SHAPE_7D:
            // Block 7D:  Draw (m+2,n)(m+1,n)(m,n)(m,n+1)
            if(this->m+2 < GAME_MAX_X - 1)
            {
                if(gameParent->gameBlock[m+3][n]==NULL && gameParent->gameBlock[m+1][n+1]==NULL)
                {
                    this->moveBlock(m+2,n,m+3,n);
                    this->moveBlock(m+1,n,m+2,n);
                    this->moveBlock(m,n,m+1,n);
                    this->moveBlock(m,n+1,m+1,n+1);
                    m++;
                }
            }
            break;
    }



}

void logic::rotateShape()
{

    // Shape rotator
    // Depending on its shape, just move some block to another point

    switch(this->newShapeType)
    {
        case SHAPE_1A:
            // Block 1A:  Draw (m-1,n)(m,n)(m+1,n)(m+2,n)
            // Rotated to 1B: to (m,n-1)(m,n)(m,n+1)(m,n+2)
            if(gameParent->gameBlock[m][n+2]==NULL && gameParent->gameBlock[m][n+1]==NULL && gameParent->gameBlock[m][n-1]==NULL)
            {
                this->moveBlock(m-1,n,m,n-1);
                this->moveBlock(m+1,n,m,n+1);
                this->moveBlock(m+2,n,m,n+2);
                this->newShapeType = SHAPE_1B;
            }
            break;
        case SHAPE_1B:
            // Block 1B:  Draw (m,n-1)(m,n)(m,n+1)(m,n+2)
            // Rotated to 1A: to (m-1,n)(m,n)(m+1,n)(m+2,n)
            if(gameParent->gameBlock[m+2][n]==NULL && gameParent->gameBlock[m+1][n]==NULL && gameParent->gameBlock[m-1][n]==NULL)
            {
                this->moveBlock(m,n-1,m-1,n);
                this->moveBlock(m,n+1,m+1,n);
                this->moveBlock(m,n+2,m+2,n);
                this->newShapeType = SHAPE_1A;
            }
            break;
        case SHAPE_2A:
            // Block 2A:  Draw (m,n)(m+1,n)(m,n-1)(m+1,n+1)
            // Rotated to 2B: to (m,n)(m-1,n)(m,n+1)(m+1,n+1)
            if(gameParent->gameBlock[m-1][n]==NULL && gameParent->gameBlock[m+1][n+1]==NULL )
            {
                this->moveBlock(m,n-1,m-1,n);
                this->moveBlock(m+1,n,m,n-1);
                this->moveBlock(m+1,n+1,m+1,n-1);
                this->newShapeType = SHAPE_3B;
            }
            break;
        case SHAPE_2B:
            // Block 2B:  Draw (m,n)(m-1,n)(m,n+1)(m+1,n+1)
            // Rotated to 2A: to (m,n)(m+1,n)(m,n-1)(m+1,n+1);
            if(gameParent->gameBlock[m-1][n+1]==NULL && gameParent->gameBlock[m][n-1]==NULL )
            {
                this->moveBlock(m+1,n+1,m+1,n-1);
                this->moveBlock(m,n+1,m+1,n);
                this->moveBlock(m-1,n,m,n+1);
                this->newShapeType = SHAPE_3A;
            }
            break;
        case SHAPE_3A:
            // Block 3A:  Draw (m,n)(m,n+1)(m-1,n)(m-1,n-1)
            if(gameParent->gameBlock[m-1][n]==NULL && gameParent->gameBlock[m+1][n+1]==NULL )
            {
                this->moveBlock(m,n+1,m-1,n);
                this->moveBlock(m+1,n,m,n+1);
                this->moveBlock(m+1,n-1,m+1,n+1);
                this->newShapeType = SHAPE_2B;
            }
            break;
        case SHAPE_3B:
            // Block 3B:  Draw (m,n)(m-1,n)(m,n-1)(m+1,n-1)
            if(gameParent->gameBlock[m+1][n+1]==NULL && gameParent->gameBlock[m][n+1]==NULL )
            {
                this->moveBlock(m+1,n-1,m+1,n+1);
                this->moveBlock(m,n-1,m+1,n);
                this->moveBlock(m-1,n,m,n-1);
                this->newShapeType = SHAPE_2A;
            }
            break;
        /*case SHAPE_4:
            // Block 4:  Draw (m,n)(m,n+1)(m+1,n)(m+1,n+1)
            if(this->m > 0)
            {
                this->moveBlock(m,n,m-1,n);
                this->moveBlock(m,n+1,m-1,n+1);
                this->moveBlock(m+1,n,m,n);
                this->moveBlock(m+1,n+1,m,n+1);
                this->m--;
            }*/
            break;
        case SHAPE_5A:
            // Block 5A:  Draw (m+1,n)(m,n+1)(m-1,n)
            if(gameParent->gameBlock[m][n-1]==NULL)
            {
                this->moveBlock(m-1,n,m,n-1);
                this->moveBlock(m,n+1,m-1,n);
                this->moveBlock(m+1,n,m,n+1);
                this->newShapeType = SHAPE_5C;
            }
            break;
        case SHAPE_5B:
            // Block 5B:  Draw (m,n-1)(m+1,n)(m,n+1)
            if(gameParent->gameBlock[m-1][n]==NULL)
            {
                this->moveBlock(m,n+1,m-1,n);
                this->moveBlock(m+1,n,m,n+1);
                this->moveBlock(m,n-1,m+1,n);
                this->newShapeType = SHAPE_5A;
            }
            break;
        case SHAPE_5C:
            // Block 5c:  Draw (m,n+1)(m-1,n)(m,n-1)
            if(gameParent->gameBlock[m+1][n]==NULL)
            {
                this->moveBlock(m,n-1,m+1,n);
                this->moveBlock(m-1,n,m,n-1);
                this->moveBlock(m,n+1,m-1,n);
                this->newShapeType = SHAPE_5D;
            }
            break;
        case SHAPE_5D:
            // Block 5D:  Draw (m-1,n)(m,n-1)(m+1,n)
            if(gameParent->gameBlock[m][n+1]==NULL)
            {
                this->moveBlock(m+1,n,m,n+1);
                this->moveBlock(m,n-1,m+1,n);
                this->moveBlock(m-1,n,m,n-1);
                this->newShapeType = SHAPE_5B;
            }
            break;
        case SHAPE_6A:
            // Block 6A:  Draw (m,n-1)(m+1,n)(m+2,n)
            if(gameParent->gameBlock[m][n+1]==NULL && gameParent->gameBlock[m][n+2]==NULL)
            {
                this->moveBlock(m+1,n,m,n+1);
                this->moveBlock(m+2,n,m,n+2);
                this->moveBlock(m,n-1,m+1,n);
                this->newShapeType = SHAPE_6B;
            }
            break;
        case SHAPE_6B:
            // Block 6B:  Draw (m+1,n)(m,n+1)(m,n+2)
            if(gameParent->gameBlock[m-2][n]==NULL && gameParent->gameBlock[m-1][n]==NULL)
            {
                this->moveBlock(m,n+1,m-1,n);
                this->moveBlock(m,n+2,m-2,n);
                this->moveBlock(m+1,n,m,n+1);
                this->newShapeType = SHAPE_6D;
            }
            break;
        case SHAPE_6C:
            // Block 6C:  Draw (m-1,n)(m,n-1)(m,n-2)
            if(gameParent->gameBlock[m+1][n]==NULL && gameParent->gameBlock[m+2][n]==NULL)
            {
                this->moveBlock(m,n-1,m+1,n);
                this->moveBlock(m,n-2,m+2,n);
                this->moveBlock(m-1,n,m,n-1);
                this->newShapeType = SHAPE_6A;
            }
            break;
        case SHAPE_6D:
            // Block 6D:  Draw (m,n+1)(m-1,n)(m-2,n)
            if(gameParent->gameBlock[m][n-1]==NULL && gameParent->gameBlock[m][n-2]==NULL)
            {
                this->moveBlock(m-1,n,m,n-1);
                this->moveBlock(m-2,n,m,n-2);
                this->moveBlock(m,n+1,m-1,n);
                this->newShapeType = SHAPE_6C;
            }
            break;
        case SHAPE_7A:
            // Block 6A:  Draw (m,n-1)(m-1,n)(m-2,n)
            if(gameParent->gameBlock[m][n-2]==NULL && gameParent->gameBlock[m+1][n]==NULL)
            {
                this->moveBlock(m,n-1,m+1,n);
                this->moveBlock(m-1,n,m,n-1);
                this->moveBlock(m-2,n,m,n-2);
                this->newShapeType = SHAPE_7C;
            }
            break;
        case SHAPE_7B:
            // Block 7B:  Draw (m-1,n)(m,n+1)(m,n+2)
            if(gameParent->gameBlock[m-2][n]==NULL && gameParent->gameBlock[m][n-1]==NULL)
            {
                this->moveBlock(m-1,n,m,n-1);
                this->moveBlock(m,n+1,m-1,n);
                this->moveBlock(m,n+2,m-2,n);
                this->newShapeType = SHAPE_7A;
            }
            break;
        case SHAPE_7C:
            // Block 7C:  Draw (m+1,n)(m,n-1)(m,n-2)
            if(gameParent->gameBlock[m][n+1]==NULL && gameParent->gameBlock[m+2][n]==NULL)
            {
                this->moveBlock(m+1,n,m,n+1);
                this->moveBlock(m,n-1,m+1,n);
                this->moveBlock(m,n-2,m+2,n);
                this->newShapeType = SHAPE_7D;
            }
            break;
        case SHAPE_7D:
            // Block 7D:  Draw (m,n+1)(m+1,n)(m+2,n)
            if(gameParent->gameBlock[m-1][n]==NULL && gameParent->gameBlock[m][n+2]==NULL)
            {
                this->moveBlock(m,n+1,m-1,n);
                this->moveBlock(m+1,n,m,n+1);
                this->moveBlock(m+2,n,m,n+2);
                this->newShapeType = SHAPE_7B;
            }
            break;

    }

}



void logic::destroyLine()
{

}

void logic::clearBlock()
{   int i, j;

    // Clear game matrix
    for(i=0;i<GAME_MAX_X;i++)
    {
        for(j=0;j<GAME_MAX_Y;j++)
        {
            //cout << "Deleting block (" <<  i << "," << j << ") ";
            if(gameParent->gameBlock[i][j]!=NULL)
            {
                //cout << "[POINTER DELETED]";
                delete gameParent->gameBlock[i][j];
            }
            //cout << endl;
            gameParent->gameBlock[i][j] = NULL;
        }
    }
    //rectfill(screen, 10, 10, 340, 460, GAME_CANVAS_BACKGROUND);

    //cout << "All block cleared" << endl;
}

void logic::resetState()
{
    this->gameState = GAME_STATE_NEWSHAPE_COMEOUT;
}
