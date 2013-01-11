#include "game.h"
#include "main.h"

// Game abstract class implementation

// printMatrices: Only for debug
/*
void game::printMatrices()
{
    int m = gameLogic->m;
    int n = gameLogic->n;

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

void interfaceTetris::requestPlayerName()
{
    const int playerNameSize = 50;
    char input[playerNameSize], n;
    string input_str;

    // Draw popup window in front of games
    blit(this->newPlayerPopup, screen, 0, 0, 53.5 , 115, 533, 250);


    // START KEYCODE READER -- SRC: http://www.gamedev.net/page/resources/_/technical/game-programming/text-input-in-an-allegro-game-r2130 //
    // OMG Still buggy and couldn't be implemented
    readkey();

    do
    {
      if(keypressed())
      {
         int  newkey   = readkey();
         char ASCII    = newkey & 0xff;
         char scancode = newkey >> 8;


         if(ASCII >= 32 && ASCII <= 126)
         {
                                if(n < playerNameSize - 1)
                                {
                                        input[n] = ASCII;
                                        n++;
                                        input[n] = '\0';
                                }
         }
         else if(scancode == KEY_BACKSPACE)
         {
            if (n > 0) n--;
            input[n] = '\0';
         }
      }

      textout_ex(screen, this->gameFontBig, input, 53.5 + 10, 115+100, COLOR_WHITE, 0);

    }


    while(!key[KEY_ENTER]);

    // END KEYCODE READER //

    // Set new score
    input_str = string(input);
    this->newScore(input_str);



    // Restore game interface
    this->initScreen();

}

void interfaceTetris::initScreen()
{
    // Display Background
    this->redrawBackground();

    // Draw game Canvas
    this->gameCanvas->redrawBorder();

    // Display Next Shape
    this->gameNextShape->redrawNextShape();

    // Display score board

}

void interfaceTetris::newGame()
{
    // Clear the game screen
    //cout << "Clear all game block" << endl;
    this->gameLogic->clearBlock();

    // Start with new shape come out
    //cout << "Set gamestate to GAME_STATE_NEWSHAPE_COMEMOUT" << endl;
    this->gameLogic->resetState();

    // Input player name
    //this->requestPlayerName();

    // Wait for user to press ENTER
    while(!key[KEY_ENTER]);

    // Play the music
    this->gameMusic->playMusic(MUSIC_NUM_1);

    // OK, game loop starter until you are game over
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
    this->gameNextShape = new nextshape();
    this->gameMusic = new music();

    // Get some image
    this->background = load_bitmap("background.pcx", NULL);
    this->newPlayerPopup = load_bitmap("player_name.bmp", NULL);
    this->gameFontBig = load_font("font.pcx", this->pallete, NULL);
}

void game::gameLoop()
{
    // Choose random new shape
    gameLogic->set_nextShapeType(rand() % 18);
    gameLogic->set_nextShapeColor(rand() % 5);
    //cout << "New Shape Type is " << nextShapeType << endl;

    // OK now start the game loop
    //cout << "[GAME LOOP STARTED]" << endl;

    while(!gameOver)
    {
        // Draw next shape type

        this->gameNextShape->setNextShapeType(this->gameLogic->get_nextShapeType(), this->gameLogic->get_nextShapeColor());
        this->gameNextShape->redrawNextShape();
        // Draw score board


        // Draw a game
        // Game iteration start here
        gameOver = gameLogic->gameLogicIteration();

    }

    // Game over state, now freeze the game screen
    // Show game over text


}


void game::newScore(string playerName)
{
    // Remove previous score
    if(this->gameScore != NULL)
    {
        delete this->gameScore;
    }

    // Create new score instantiation.
    this->gameScore = new score(playerName);

    // Done

}


void game::redrawBackground()
{
    blit(background, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}
