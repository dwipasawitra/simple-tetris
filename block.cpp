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

BITMAP* block::blockImageCollection[BLOCK_COLOR_TOTAL];

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
        blockImage = blockImageCollection[BLOCK_COLOR_BLACK];
        break;
    case BLOCK_COLOR_BLUE:
        blockImage = blockImageCollection[BLOCK_COLOR_BLUE];
        break;
    case BLOCK_COLOR_GREEN:
        blockImage = blockImageCollection[BLOCK_COLOR_GREEN];
        break;
    case BLOCK_COLOR_RED:
        blockImage = blockImageCollection[BLOCK_COLOR_RED];
        break;
    case BLOCK_COLOR_YELLOW:
        blockImage = blockImageCollection[BLOCK_COLOR_YELLOW];
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

void block::loadBlockImage()
{
    cout << "Loaded block image" << endl;
    block::blockImageCollection[BLOCK_COLOR_BLACK] = load_bitmap("block_black.pcx", NULL);
    block::blockImageCollection[BLOCK_COLOR_BLUE] = load_bitmap("block_blue.pcx", NULL);
    block::blockImageCollection[BLOCK_COLOR_GREEN] = load_bitmap("block_green.pcx", NULL);
    block::blockImageCollection[BLOCK_COLOR_YELLOW] = load_bitmap("block_yellow.pcx", NULL);
    block::blockImageCollection[BLOCK_COLOR_RED] = load_bitmap("block_red.pcx", NULL);
}

void block::unloadBlockImage()
{
    destroy_bitmap(block::blockImageCollection[BLOCK_COLOR_BLACK]);
    destroy_bitmap(block::blockImageCollection[BLOCK_COLOR_BLUE]);
    destroy_bitmap(block::blockImageCollection[BLOCK_COLOR_GREEN]);
    destroy_bitmap(block::blockImageCollection[BLOCK_COLOR_YELLOW]);
    destroy_bitmap(block::blockImageCollection[BLOCK_COLOR_RED]);
}
