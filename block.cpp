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

int block::getColor()
{
    return this->blockColor;
}

void block::setColor(int newColor)
{
    this->blockColor = newColor;
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
    this->setColor(newColor);
    this->setState(newBlockState);
}
