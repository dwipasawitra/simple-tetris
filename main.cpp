#include "tetris.h"
#include "main.h"

int main()
{
	// Game instatination and start
	srand(time(NULL));
    tetris *gameWindow = new tetris(0);
    gameWindow->start();

    return 0;
}
END_OF_MAIN();
