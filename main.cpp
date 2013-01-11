#include "tetris.h"
#include "main.h"

void initAllegro()
{
    /* Allegro Initializer */
    allegro_init();
    install_keyboard();     // Install keyboard driver
    install_timer();        // Install timer driver
    set_color_depth(desktop_color_depth());

    // Install sound driver
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
        allegro_message("Error initializing sound system\n%s\n", allegro_error);


    }

    cout << "Allegro initialization success" << endl;
}
int main()
{
	// Game instatination and start
	initAllegro();
	srand(time(NULL));
    tetris *gameWindow = new tetris(TETRIS_INTERFACE_MENU);
    gameWindow->start();
    return 0;
}
END_OF_MAIN();
