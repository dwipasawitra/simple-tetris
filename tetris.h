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

#pragma once
#include "main.h"
#include "highscores.h"
#include "game.h"




class tetris
{
private:
    int interfaceState;
    //highscores *scoresData;
    interfaceTetris *gameIface;

    void initWindow();
    void clearWindow();
    void destroyWindow();
public:
    void start();       // Start game method
    void mainMenu();    // Open Main menu interface
    void tetrisInterface(); // Open Tetris interface
    void highScores();  // Open highscore interface

    tetris(int startInterface);
    ~tetris();
};
