#include "nextshape.h"

void nextshape::setNextShapeType(int nextShapeType, int nextShapeColor)
{
    int i, j, countBlock;
    int m, n;
    this->nextShapeType = nextShapeType;
    this->nextShapeColor = nextShapeColor;


    // Delete previous block

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(this->nextShapeBlock[i][j] != NULL)
            {
                delete nextShapeBlock[i][j];
                this->nextShapeBlock[i][j] = NULL;
            }
        }
    }


    // Initialize the new block
    block *block1 = new block(this->nextShapeColor, BLOCK_STATE_DUMMY);
    block *block2 = new block(this->nextShapeColor, BLOCK_STATE_DUMMY);
    block *block3 = new block(this->nextShapeColor, BLOCK_STATE_DUMMY);
    block *block4 = new block(this->nextShapeColor, BLOCK_STATE_DUMMY);

    //9cout << this->nextShapeType << endl;

    // Heap the block, depending on its type
    switch(this->nextShapeType)
    {
        case SHAPE_1A:
            // Block 1A:  Draw (m-1,n)(m,n)(m+1,n)(m+2,n)
            m = 1; n = 0;
            this->nextShapeBlock[m-1][n] = block1;
            this->nextShapeBlock[m][n] = block2;
            this->nextShapeBlock[m+1][n] = block3;
            this->nextShapeBlock[m+2][n] = block4;
            break;
        case SHAPE_1B:
            // Block 1B:  Draw (m,n-1)(m,n)(m,n+1)(m,n+2)
            m = 2; n = 1;
            this->nextShapeBlock[m][n-1] = block1;
            this->nextShapeBlock[m][n] = block2;
            this->nextShapeBlock[m][n+1] = block3;
            this->nextShapeBlock[m][n+2] = block4;
            break;
        case SHAPE_2A:
            // Block 2A:  Draw (m,n)(m+1,n)(m,n-1)(m+1,n+1)
            m = 1; n = 1;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m+1][n] = block2;
            this->nextShapeBlock[m][n-1] = block3;
            this->nextShapeBlock[m+1][n+1] = block4;
            break;
        case SHAPE_2B:
            // Block 2B:  Draw (m,n)(m-1,n)(m,n+1)(m+1,n+1)
            m = 1; n = 0;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m-1][n] = block2;
            this->nextShapeBlock[m][n+1] = block3;
            this->nextShapeBlock[m+1][n+1] = block4;
            break;
        case SHAPE_3A:
            // Block 3A:  Draw (m,n)(m,n+1)(m-1,n)(m-1,n-1)
            m = 1; n = 1;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m][n+1] = block2;
            this->nextShapeBlock[m+1][n] = block3;
            this->nextShapeBlock[m+1][n-1] = block4;
            break;
        case SHAPE_3B:
            // Block 3B:  Draw (m,n)(m-1,n)(m,n-1)(m+1,n-1)
            m = 1; n = 1;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m-1][n] = block2;
            this->nextShapeBlock[m][n-1] = block3;
            this->nextShapeBlock[m+1][n-1] = block4;
            break;
        case SHAPE_4:
            // Block 4:  Draw (m,n)(m,n+1)(m+1,n)(m+1,n+1)
            m = 0; n = 0;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m][n+1] = block2;
            this->nextShapeBlock[m+1][n] = block3;
            this->nextShapeBlock[m+1][n+1] = block4;
            break;
        case SHAPE_5A:
            // Block 5A: Draw (m,n) (m+1,n) (m-1,n) (m,n+1)
            m = 2; n = 2;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m+1][n] = block2;
            this->nextShapeBlock[m-1][n] = block3;
            this->nextShapeBlock[m][n+1] = block4;
            break;
        case SHAPE_5B:
            // Block 5B : Draw (m,n) (m+1,n) (m,n+1) (m,n-1)
            m = 2; n = 2;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m+1][n] = block2;
            this->nextShapeBlock[m][n+1] = block3;
            this->nextShapeBlock[m][n-1] = block4;
            break;
        case SHAPE_5C:
            // Block 5C : Draw (m,n) (m-1,n) (m,n+1) (m,n-1)
            m = 2; n = 2;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m-1][n] = block2;
            this->nextShapeBlock[m][n+1] = block3;
            this->nextShapeBlock[m][n-1] = block4;
            break;
        case SHAPE_5D:
            //Block 5D : Draw (m,n)(m-1,n) (m+1,n) (m,n-1)
            m = 2; n = 2;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m-1][n] = block2;
            this->nextShapeBlock[m+1][n] = block3;
            this->nextShapeBlock[m][n-1] = block4;
            break;
        case SHAPE_6A:
            //Block 6A :  Draw (m,n) (m+1,n) (m+2,n) (m,n-1)
            m = 1; n = 1;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m+1][n] = block2;
            this->nextShapeBlock[m+2][n] = block3;
            this->nextShapeBlock[m][n-1] = block4;
            break;
        case SHAPE_6B:
            //BLOCK 6B : Draw (m,n) (m+1,n) (m,n+1) (m,n+2)
            m = 1; n = 1;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m+1][n] = block2;
            this->nextShapeBlock[m][n+1] = block3;
            this->nextShapeBlock[m][n+2] = block4;
            break;
        case SHAPE_6C:
            //BLOCK 6C : Draw (m,n) (m-1,n) (m,n-1) (m,n-2)
            m = 2; n = 3;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m-1][n] = block2;
            this->nextShapeBlock[m][n-1] = block3;
            this->nextShapeBlock[m][n-2] = block4;
            break;
        case SHAPE_6D:
            //BLOCK 6D : Draw (m,n) (m-1,n) (m-2,n) (m,n+1)
            m = 3; n = 1;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m-1][n] = block2;
            this->nextShapeBlock[m-2][n] = block3;
            this->nextShapeBlock[m][n+1] = block4;
            break;
        case SHAPE_7A:
            //BLOCK 7A : Draw (m,n) (m,n-1) (m-1,n) (m-2,n)
            m = 2; n = 3;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m][n-1] = block2;
            this->nextShapeBlock[m-1][n] = block3;
            this->nextShapeBlock[m-2][n] = block4;
            break;
        case SHAPE_7B:
            //BLOCK 7B : Draw (m,n) (m-1,n) (m,n+1) (m,n+2)
            m = 2; n = 1;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m-1][n] = block2;
            this->nextShapeBlock[m][n+1] = block3;
            this->nextShapeBlock[m][n+2] = block4;
            break;
        case SHAPE_7C:
            //BLOCK 7C : Draw (m,n) (m+1,n) (m,n-1) (m,n-2)
            m = 1; n = 3;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m+1][n] = block2;
            this->nextShapeBlock[m][n-1] = block3;
            this->nextShapeBlock[m][n-2] = block4;
            break;
        case SHAPE_7D:
            //BLOCK 7D : Draw (m,n) (m+1,n) (m+2,n) (m,n+1)
            m = 1; n = 1;
            this->nextShapeBlock[m][n] = block1;
            this->nextShapeBlock[m+1][n] = block2;
            this->nextShapeBlock[m+2][n] = block3;
            this->nextShapeBlock[m][n+1] = block4;
            break;
    }

}
int nextshape::getNextShapeType()
{
    return this->nextShapeType;
}
void nextshape::redrawNextShape()
{
    int i, j;
    int drawPointX, drawPointY;
    block *currentBlock;

    // Load next shape border
    this->nextShapeBorder = load_bitmap("nextshape.bmp", NULL);

    // Blit it into screen
    blit(this->nextShapeBorder, screen, 0, 0, GAME_NEXTSHAPE_START_X, GAME_NEXTSHAPE_START_Y, GAME_NEXTSHAPE_WIDTH, GAME_NEXTSHAPE_HEIGHT);

    // Draw the block depending on its variabel
    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            if(nextShapeBlock[i][j]!=NULL)
            {
                drawPointX = (20*i) + GAME_NEXTSHAPE_START_X + GAME_NEXTSHAPE_BLOCK_START_X;
                drawPointY = (20*j) + GAME_NEXTSHAPE_START_Y + GAME_NEXTSHAPE_BLOCK_START_Y;

                blit(nextShapeBlock[i][j]->getImage(), screen, 0, 0, drawPointX, drawPointY, 20, 20);

            }
            else
            {
                drawPointX = (20*i) + GAME_NEXTSHAPE_START_X + GAME_NEXTSHAPE_BLOCK_START_X;
                drawPointY = (20*j) + GAME_NEXTSHAPE_START_Y + GAME_NEXTSHAPE_BLOCK_START_Y;

                blit(this->nextShapeBorder, screen, drawPointX, drawPointY, drawPointX, drawPointY, 20, 20);
            }
        }
    }


}

nextshape::nextshape()
{
    int i, j;
    this->nextShapeType = NULL;

    for(i=0;i<4;i++)
    {
        for(j=0;j<4;j++)
        {
            this->nextShapeBlock[i][j] = NULL;
        }
    }
}
