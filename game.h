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
#include "music.h"
#include "score.h"
#include "highscores.h"

class game
{
friend class control;
friend class logic;
friend class canvas;
protected:
    // Allegro Element
    FONT* gameFontBig;
    BITMAP* background;
    BITMAP* gameBorder;
    BITMAP* newPlayerPopup;
    BITMAP* pausePopup;
    BITMAP* gameOverPopup;
    PALLETE pallete;

    // Game Element
    block *gameBlock[GAME_MAX_X][GAME_MAX_Y];
    canvas *gameCanvas;
    control *gameControl;
    nextshape *gameNextShape;
    logic *gameLogic;
    music *gameMusic;
    score *gameScore;

    int selectedMidi;

    // Game variabel
    bool gameOver;

    // Game Element method
    void gameLoop();
    void initScreen();
    void pauseGame();
    void abortGame();


    void newScore(string playerName);
    void redrawBackground();

public:
    game();
    ~game();
};

// interfaceTetris class: Abstracting Game Interface Element System with User
class interfaceTetris : public game
{

public:
    void requestPlayerName();
    void gameOverInterface();
    void newGame();

    interfaceTetris();
};

