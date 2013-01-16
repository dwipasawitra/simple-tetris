#pragma once
#include "game.h"

class control
{
private:
    game *gameParent;
    void controlLeft();
    void controlRight();
    void controlTurbo();
public:
    void receiveControl();
    void receiveControlLr();
    void receiveOnlyTurbo();


    control(game *gameParent);
};
