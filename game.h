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

#include "highscores.h"
#include "block.h"
#include "canvas.h"
#include "logic.h"
#include "control.h"
#include "main.h"
#include "nextshape.h"

class game
{
friend class control;
friend class logic;
friend class canvas;
protected:
    FONT* gameFont;
    BITMAP* background;
    BITMAP* gameBorder;
    PALLETE pallete;

    string playerName;
    block *gameBlock[GAME_MAX_X][GAME_MAX_Y];
    canvas *gameCanvas;
    control *gameControl;
    nextshape *gameNextShape;
    logic *gameLogic;
    bool gameOver;
    int gameScores;
    void gameLoop();
    void newScore();
    //void printMatrices();

public:
    game();
    ~game();
};

class interfaceTetris : public game
{

public:
    void initScreen();
    void requestPlayerName();
    interfaceTetris();
    void newGame();
    void stopGame();
};

