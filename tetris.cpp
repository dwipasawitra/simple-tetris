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
    cout << "Class started" << endl;
    /* Allegro Initializer */
    allegro_init();
    install_keyboard();     // Install keyboard driver
    install_timer();        // Install timer driver
    set_color_depth(desktop_color_depth());

    // Install sound driver
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
        allegro_message("Error initializing sound system\n%s\n", allegro_error);


    }


    /* Game Font Experiment */
    gameFont = load_font("font.pcx", pallete, NULL);
    if (!gameFont)
         cout << "Couldn't load font!";
    /* End of Game Font Experiment */

    /* Create a new Window */
    if(os_type == OSTYPE_LINUX)
    {
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    }
    else
    {
//        set_gfx_mode(GFX_GDI, 640, 480, 0, 0);

    }


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
    hsIface = new interfaceHighScore();

    // Open a window depending the state
    while(1)
    {
        switch(this->interfaceState)
        {
        case TETRIS_INTERFACE_MENU:
            this->mainMenu();
            break;
        case TETRIS_INTERFACE_GAME:
            this->tetrisInterface();
            break;
        case TETRIS_INTERFACE_HIGHSCORE:
            this->highScores();
            break;
        }
    }

}

void tetris::mainMenu()    // Open Main menu interface
{
    int selection;
    bool selected = false;

    // First, clear screen
    this->clearWindow();

    cout << "Menu show";

    // Draw a selection text
    // Change "font" to "gameFont" to implement font experiment
    textout_centre_ex(screen, gameFont, "TETRIS", SCREEN_W/2, 40, COLOR_WHITE, 0);
    textout_centre_ex(screen, gameFont, "1. Mulai Permainan", SCREEN_W/2, 80, COLOR_WHITE,0);
    textout_centre_ex(screen, gameFont, "2. Skor tertinggi", SCREEN_W/2, 113, COLOR_WHITE, 0);
    textout_centre_ex(screen, gameFont, "3. Tentang permainan ini", SCREEN_W/2, 146, COLOR_WHITE, 0);

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

    // Initialization game Interface
    gameIface->initScreen();

    // Now interfaceTetris class will do the rest thing;
    gameIface->newGame();
}

void tetris::highScores()  // Open highscore interface
{
    this->clearWindow();

    hsIface->displayHighScore();
}

tetris::tetris(int startInterface)
{
    interfaceState = startInterface;
}
tetris::~tetris()
{

}
