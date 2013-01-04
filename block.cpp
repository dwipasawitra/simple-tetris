/* simple-tetris Game
 * Built using Allegro library
 * https://github.com/initrunlevel0/simple-tetris
 *
 * Author :
 * Putu Wiramaswara Widya
 * Reinhard Ruben R.
 *
 * Created for Object Oriented Programming (KI091311) Class
 * at Informatics Departmennt, Institut Teknologi Sepuluh Nopember (ITS)
 * Surabaya, Indonesia
 */


#include "block.h"

BITMAP *block::getImage()
{
    return blockImage;
}

void block::setColor(int newColor)
{
    // Depending on its color, choose the right bitmap

    switch(newColor)
    {

    case BLOCK_COLOR_BLACK:
        this->blockImage = load_bitmap("block_black.bmp", NULL);
        break;
    case BLOCK_COLOR_BLUE:
        this->blockImage = load_bitmap("block_blue.bmp", NULL);
        break;
    case BLOCK_COLOR_GREEN:
        this->blockImage = load_bitmap("block_green.bmp", NULL);
        break;
    case BLOCK_COLOR_RED:
        this->blockImage = load_bitmap("block_red.bmp", NULL);
        break;
    case BLOCK_COLOR_YELLOW:
        this->blockImage = load_bitmap("block_yellow.bmp", NULL);
        break;

    }
}

int block::getState()
{
    return this->state;
}

void block::setState(int newBlockState)
{
    this->state = newBlockState;
}

block::block(int newColor, int newBlockState)
{
    // Set bitmap depending on its color
    this->setColor(newColor);
    this->setState(newBlockState);
}
