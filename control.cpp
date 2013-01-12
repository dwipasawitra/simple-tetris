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
        gameParent->gameCanvas->redrawGraphic();
        rest(GAME_LOOP_SPEED_TICKSPEED);
        /*while(key[KEY_LEFT] && n>0)
        {
            gameParent->gameLogic->moveLeft();
            gameParent->gameCanvas->redrawGraphic();
            n--;
            rest(GAME_LOOP_SPEED_TURBO);
        }*/
    }
    if(key[KEY_RIGHT])
    {
        gameParent->gameLogic->moveRight();
        gameParent->gameCanvas->redrawGraphic();
        rest(GAME_LOOP_SPEED_TICKSPEED);
        /*while(key[KEY_RIGHT] && n>0)
        {
            gameParent->gameLogic->moveRight();
            gameParent->gameCanvas->redrawGraphic();
            n--;
            rest(GAME_LOOP_SPEED_TURBO);
        }*/
    }
    if(key[KEY_UP])
    {
        gameParent->gameLogic->rotateShape();
        rest(GAME_LOOP_SPEED_TICKSPEED);
    }
    if(key[KEY_ESC])
    {
        gameParent->pauseGame();
    }

}

void control::receiveOnlyTurbo()
{
    if(key[KEY_DOWN])
    {
        gameParent->gameLogic->gameLoopSpeed = GAME_LOOP_SPEED_TURBO;
        gameParent->gameLogic->tickSpeed = 2;
    }
    else gameParent->gameLogic->gameLoopSpeed = GAME_LOOP_SPEED_NORMAL;
}
