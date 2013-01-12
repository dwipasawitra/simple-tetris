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
        set_gfx_mode(GFX_GDI, 640, 480, 0, 0);

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



    // Open a window depending the state
    while(1)
    {
        switch(this->interfaceState)
        {
        case TETRIS_INTERFACE_MENU:
            this->mainMenu();
            break;
        case TETRIS_INTERFACE_GAME:
            gameIface = new interfaceTetris();
            this->tetrisInterface();
            break;
        case TETRIS_INTERFACE_HIGHSCORE:
            hsIface = new interfaceHighScore();

            this->highScores();
            break;
        }
    }

}

void tetris::mainMenu()    // Open Main menu interface
{
    BITMAP *buffer;
    int selection = 0;
    bool selected = false;

    // First, clear screen
    this->clearWindow();

    cout << "Menu show";

    // Copy background to buffer
    buffer = create_bitmap(640, 480);
    draw_sprite(buffer, this->menuBackground, 0, 0);

    // Draw logo
    draw_sprite(buffer, this->logoBig, 110, 50);


    // Draw menu item
    draw_sprite(buffer, this->menuItem, 120, 200);
    blit(buffer, screen, 0, 0, 0, 0, 640, 480);

    while(!selected)
    {
        // Clear selection part first
        blit(this->menuBackground, buffer, 88, 200, 88, 200, 34, 191);


        // Redraw selection position
        draw_sprite(buffer, this->menuSelection, 88, selection * 51 + 200);
        blit(buffer, screen, 0, 0, 0, 0, 640, 480);

        // Check keystroke
        if(key[KEY_UP])
        {
            if(selection > 0) selection--;
            while(key[KEY_UP]);
        }
        else if(key[KEY_DOWN])
        {
            if(selection < 3) selection++;
            while(key[KEY_DOWN]);
        }
        else if(key[KEY_ENTER])
        {
            while(key[KEY_ENTER]);
            switch(selection)
            {
                case 0:
                    this->interfaceState = TETRIS_INTERFACE_GAME;
                    selected = true;
                    break;
                case 1:
                    this->interfaceState = TETRIS_INTERFACE_HIGHSCORE;
                    selected = true;
                    break;

            }
        }


    }

}
void tetris::tetrisInterface() // Open Tetris interface
{
    this->clearWindow();

    // Now interfaceTetris class will do the rest thing;
    gameIface->newGame();

    // After game done and back to menu, here we goes
    this->interfaceState = TETRIS_INTERFACE_MENU;


}

void tetris::highScores()  // Open highscore interface
{
    this->clearWindow();

    hsIface->reloadHighScore();
    hsIface->displayHighScore();


    while(!key[KEY_ESC]) { }
    this->interfaceState = TETRIS_INTERFACE_MENU;

}

tetris::tetris(int startInterface)
{
    interfaceState = startInterface;

    // Load some bitmap
    this->menuBackground = load_bitmap("menu.bmp", NULL);
    this->logoBig = load_bitmap("tetris-logo-big.bmp", NULL);
    this->menuSelection = load_bitmap("selection.bmp", NULL);
    this->menuItem = load_bitmap("menu-item.bmp", NULL);


}
tetris::~tetris()
{

}
