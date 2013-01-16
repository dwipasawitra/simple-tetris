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
        rest(GAME_LOOP_MOVEWAIT);
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
        rest(GAME_LOOP_MOVEWAIT);
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
        while(key[KEY_UP]);
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
        gameParent->gameLogic->tickSpeed = GAME_ITERATION_TICK_TOTAL_TURBO;
    }
    else
    {
        gameParent->gameLogic->gameLoopSpeed = GAME_LOOP_SPEED_NORMAL;
        gameParent->gameLogic->tickSpeed = GAME_ITERATION_TICK_TOTAL;
    }
}
