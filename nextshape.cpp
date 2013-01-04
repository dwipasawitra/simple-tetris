#include "nextshape.h"

void nextshape::setNextShapeType()
{

}
int nextshape::getNextShapeType()
{

}
void nextshape::redrawNextShape()
{
    // Load next shape border
    this->nextShapeBorder = load_bitmap("nextshape.bmp", NULL);

    // Blit it into screen
    blit(this->nextShapeBorder, screen, 0, 0, GAME_NEXTSHAPE_START_X, GAME_NEXTSHAPE_START_Y, GAME_NEXTSHAPE_WIDTH, GAME_NEXTSHAPE_HEIGHT);

    // Show the block depending nextShapeType variabel

}
