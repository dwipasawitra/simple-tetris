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
#include "tetris.h"
#include "main.h"


void tetris::initWindow()
{
    /* Allegro Initializer */
    allegro_init();
    install_keyboard();     // Install keyboard driver
    install_timer();        // Install timer driver
    set_color_depth(16);

    /* Create a new Window */
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);


    // OK, now you can draw anything in that window :)


}

void tetris::clearWindow()
{
    // Give all 640x480 screen black;
    rectfill(screen, 0, 0, 640, 480, COLOR_BLACK);
}
void tetris::destroyWindow()
{

}

void tetris::start()       // Start game method
{
    // Init a new Allegro Window
    this->initWindow();

    // Init interfacetetris class
    gameIface = new interfaceTetris();

    // Open a window depending the state
    while(1)
    {
        switch(this->interfaceState)
        {
            case TETRIS_INTERFACE_MENU:
                this->mainMenu(); break;
            case TETRIS_INTERFACE_GAME:
                this->tetrisInterface(); break;
            case TETRIS_INTERFACE_HIGHSCORE:
                this->highScores(); break;
        }
    }

}

void tetris::mainMenu()    // Open Main menu interface
{
    int selection;
    bool selected = false;

    // First, clear screen
    this->clearWindow();

    // Draw a selection text
    textout_centre_ex(screen, font, "TETRIS", SCREEN_W/2, 40, COLOR_WHITE, 0);
    textout_centre_ex(screen, font, "1. Mulai Permainan", SCREEN_W/2, 80, COLOR_WHITE,0);
    textout_centre_ex(screen, font, "2. Skor tertinggi", SCREEN_W/2, 90, COLOR_WHITE, 0);
    textout_centre_ex(screen, font, "3. Tentang permainan ini", SCREEN_W/2, 100, COLOR_WHITE, 0);

    // OK select the menu, 1, 2 or 3
    while(!selected)
    {
        if(key[KEY_1])
        {
            this->interfaceState = TETRIS_INTERFACE_GAME;
            selected = true;
        }
        else if(key[KEY_2])
        {
            this->interfaceState = TETRIS_INTERFACE_HIGHSCORE;
            selected = true;
        }
        rest(1);   // Block fast key repeat
    }
}
void tetris::tetrisInterface() // Open Tetris interface
{
    this->clearWindow();

    // Initializing a screen for your tetris, bro
    rectfill(screen, 20, 0, 320, 480, GAME_CANVAS_BACKGROUND);

    // Wait for use to press enter
    while(!key[KEY_ENTER]);

    // Now interfaceTetris class will do the rest thing;
    gameIface->newGame();
}

void tetris::highScores()  // Open highscore interface
{

}

tetris::tetris(int startInterface)
{

}
tetris::~tetris()
{

}
