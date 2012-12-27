#include "game.h"
#include "main.h"

// Game abstract class implementation

// printMatrices: Only for debug
/*
void game::printMatrices()
{
    cout << endl;
    cout << "M = " << m << ", N = " << n << endl;
    int i, j;
    for(i=0;i<GAME_MAX_Y;i++)
    {
        for(j=0;j<GAME_MAX_X;j++)
        {
            if(this->gameBlock[j][i] == NULL) cout << "*";
            else cout << "O";
        }

        cout << endl;
    }
    cout << endl;
}
*/

// Interface Tetris class implementation
interfaceTetris::interfaceTetris()
{
    // First play, set game over to false
    this->gameOver = false;

    int i, j;

    // Clear game matrix
    for(i=0;i<GAME_MAX_X;i++)
        for(j=0;j<GAME_MAX_Y;j++)
            this->gameBlock[i][j] = NULL;
}

void interfaceTetris::newGame()
{
    // Clear the game screen
    //cout << "Clear all game block" << endl;
    this->gameLogic->clearBlock();

    // Start with new shape come out
    //cout << "Set gamestate to GAME_STATE_NEWSHAPE_COMEMOUT" << endl;
    this->gameLogic->resetState();

    // OK, game loop starter until you are game over
    //cout << "Starting Game loop.." << endl;
    this->gameLoop();
}
void interfaceTetris::stopGame()
{

}


game::game()
{
    this->gameCanvas = new canvas(this);
    this->gameControl = new control(this);
    this->gameLogic = new logic(this);
}

void game::gameLoop()
{
    // Choose random new shape
    gameLogic->set_nextShapeType(rand() % 7);
    //cout << "New Shape Type is " << nextShapeType << endl;

    // OK now start the game loop
    //cout << "[GAME LOOP STARTED]" << endl;
    gameLogic->gameLogicLoop();


}


void game::newScore(string playerName)
{

}




