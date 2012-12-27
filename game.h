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

class game
{
friend class control;
friend class logic;
friend class canvas;
protected:
    block *gameBlock[16][28];
    canvas *gameCanvas;
    control *gameControl;
    logic *gameLogic;
    bool gameOver;
    int gameScores;
    void gameLoop();
    void newScore(string playerName);

public:
    game();
    ~game();
};

class interfaceTetris : public game
{
public:
    interfaceTetris();
    void newGame();
    void stopGame();
};

