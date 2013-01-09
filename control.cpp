#include "control.h"

control::control(game *gameParent)
{
    this->gameParent = gameParent;
}

void control::receiveControl()
{

    if(key[KEY_LEFT]) gameParent->gameLogic->moveLeft();
    if(key[KEY_RIGHT]) gameParent->gameLogic->moveRight();
    if(key[KEY_UP]) gameParent->gameLogic->rotateShape();

}

void control::receiveOnlyTurbo()
{
    if(key[KEY_DOWN]) gameParent->gameLogic->gameLoopSpeed = GAME_LOOP_SPEED_TURBO;
    else gameParent->gameLogic->gameLoopSpeed = GAME_LOOP_SPEED_NORMAL;
}
