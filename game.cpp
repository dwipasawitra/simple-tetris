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
    clear_keybuf();
    strcpy(input, "");
    n=0;


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
         blit(this->newPlayerPopup, screen, 0, 0, 53.5 , 115, 533, 250);
         textout_centre_ex(screen, this->gameFontBig, input, 320, 115+100, COLOR_BLACK, -1);
      }


    }
    while(!key[KEY_ENTER] || !strcmp(input, ""));

    // END KEYCODE READER //

    // Set new score
    input_str = string(input);

    this->newScore(input_str);



    // Restore game interface
    this->initScreen();

}


void interfaceTetris::newGame()
{
    // Init screen
    this->initScreen();

    // Set game over to zero
    this->gameOver = false;

    // Clear the game screen
    //cout << "Clear all game block" << endl;
    this->gameLogic->clearBlock();

    // Start with new shape come out
    //cout << "Set gamestate to GAME_STATE_NEWSHAPE_COMEMOUT" << endl;
    this->gameLogic->resetState();

    // Input player name
    this->requestPlayerName();

    // Wait for user to press ENTER
    while(!key[KEY_ENTER]);

    // Play the music
    this->gameMusic->playMusic(this->selectedMidi);
    this->gameSound->playSound(GAME_SOUND_BEGIN);

    // OK, game loop starter until you are game over
    this->gameLoop();

    // Stop the music
    this->gameMusic->stopMusic();

    // Game over interface
    this->gameOverInterface();
}

void interfaceTetris::gameOverInterface()
{
    char scoreOutput[10]; // C compatibility
    int selected = false;

    // Display game over popup
    blit(this->gameOverPopup, screen, 0, 0, 53.5 , 115, 533, 250);

    // Display player name on popup
    textout_centre_ex(screen, this->gameFontBig, this->gameScore->readPlayerName().c_str(), 320, 175, makecol(255,255,255), -1);

    // Display player score
    sprintf(scoreOutput, "%05d", this->gameScore->readScore());
    textout_centre_ex(screen, this->gameFontBig, scoreOutput, 320, 215, makecol(255,0,0), -1);

    // Save score into highscore
    highscore::newHighScore(this->gameScore);

    // Receive control
    while(!selected)
    {
        if(key[KEY_ENTER])
        {
            // Ulangi permainan
            while(key[KEY_ENTER]);
            selected = true;
            this->newGame();
        }
        else if(key[KEY_ESC])
        {
            // Keluar dari permainan
            while(key[KEY_ESC]);
            selected = true;
        }
    }
}


game::game()
{
    this->gameCanvas = new canvas(this);
    this->gameControl = new control(this);
    this->gameLogic = new logic(this);
    this->gameNextShape = new nextshape();
    this->gameMusic = new music();
    this->gameSound = new sound();
    this->gameScore = NULL;

    // Get some image
    this->background = load_bitmap("background.pcx", NULL);
    this->newPlayerPopup = load_bitmap("player_name.bmp", NULL);
    this->gameFontBig = load_font("font.pcx", this->pallete, NULL);
    this->pausePopup = load_bitmap("paused.bmp", NULL);
    this->gameOverPopup = load_bitmap("gameover.bmp", NULL);

    this->selectedMidi = MUSIC_NUM_1;

    // Load block image
    block::loadBlockImage();
}

game::~game()
{
    delete this->gameCanvas;
    delete this->gameControl;
    delete this->gameLogic;
    delete this->gameNextShape;
    delete this->gameMusic;
    delete this->gameScore;
    delete this->gameSound;

    // Unload some image
    destroy_bitmap(this->background);
    destroy_bitmap(this->newPlayerPopup);
    destroy_bitmap(this->pausePopup);
    destroy_bitmap(this->gameOverPopup);

    // Unload block image
    block::unloadBlockImage();

}

void game::gameLoop()
{
    // Choose random new shape
    gameLogic->set_nextShapeType(rand() % 18);
    gameLogic->set_nextShapeColor(rand() % 5);
    //cout << "New Shape Type is " << nextShapeType << endl;

    // OK now start the game loop
    //cout << "[GAME LOOP STARTED]" << endl;

    while(!this->gameOver)
    {
        // Draw next shape type

        this->gameNextShape->setNextShapeType(this->gameLogic->get_nextShapeType(), this->gameLogic->get_nextShapeColor());
        this->gameNextShape->redrawNextShape();

        // Draw score board
        this->gameScore->redrawScore();

        // Draw a game
        // Game iteration start here
        gameLogic->gameLogicIteration();

    }



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


void game::pauseGame()
{
    bool selected = false;
    while(key[KEY_ESC]);

    // Pause the music
    this->gameMusic->pauseMusic();

    // Tampilkan popup untuk pause
    blit(this->pausePopup, screen, 0, 0, 53.5 , 115, 533, 250);

    // Ambil tombol perintah dari pengguna
    while(!selected)
    {
        if(key[KEY_ENTER])
        {
            // Batalkan penahanan
            while(key[KEY_ENTER]);
            selected = true;
            this->initScreen();
            this->gameMusic->resumeMusic();
        }
        else if(key[KEY_ESC])
        {
            // Keluar dari permainan
            while(key[KEY_ESC]);
            this->abortGame();
            selected = true;
        }
    }
}

void game::abortGame()
{
    // Redraw interface to make smooth transition
    this->initScreen();


    // Set true, return control to interfaceTetris class
    this->gameOver = true;


}

void game::initScreen()
{
    // Display Background
    this->redrawBackground();

    // Draw game Canvas
    this->gameCanvas->redrawBorder();
    this->gameCanvas->redrawGraphicAll();

    // Display Next Shape
    this->gameNextShape->redrawNextShape();


    // Display score board

}
