#include "control.h"

control::control(game *gameParent)
{
    this->gameParent = gameParent;
}

void control::receiveControl()
{
    int n=6;

    if(key[KEY_LEFT])
    {
        gameParent->gameLogic->moveLeft();
        gameParent->gameLogic->moveLeft();
        rest(100);
        while(key[KEY_LEFT] && n>0)
        {
            gameParent->gameLogic->moveLeft();
            gameParent->gameCanvas->redrawGraphic();
            n--;
            rest(GAME_LOOP_SPEED_TURBO);
        }
    }
    if(key[KEY_RIGHT])
    {
        gameParent->gameLogic->moveRight();
        rest(100);
        while(key[KEY_RIGHT] && n>0)
        {
            gameParent->gameLogic->moveRight();
            gameParent->gameCanvas->redrawGraphic();
            n--;
            rest(GAME_LOOP_SPEED_TURBO);
        }
    }
    if(key[KEY_UP])
    {
        gameParent->gameLogic->rotateShape();
    }

}

void control::receiveOnlyTurbo()
{
    if(key[KEY_DOWN]) gameParent->gameLogic->gameLoopSpeed = GAME_LOOP_SPEED_TURBO;
    else gameParent->gameLogic->gameLoopSpeed = GAME_LOOP_SPEED_NORMAL;
}
