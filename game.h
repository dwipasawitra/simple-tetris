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
#include "block.h"

class game
{
protected:
    block *gameBlock[16][28];
    int gameState;
    bool gameOver;
    int gameScores;
    int gameLoopSpeed;
    //highscores *scoresData;

    void gameLoop();
    void receiveControl();
    void newScore(string playerName);

    /* New shape related */
    int m, n;  // Track new shape
    int newShapeType;
    int nextShapeType;

    /* Game canvas related */
    void redrawGraphic();
    void drawBlock(int x, int y, block *property);
    void clearBlock(int x, int y);
    bool checkPoint(int x, int y);

    /* Block matrix control */
    void newShape(int newShapeType);
    bool collideDetect();
    void setAllStoned();
    void moveBlock(int x1, int y1, int x2, int y2);
    void goDown();
    void moveLeft();
    void moveRight();
    void destroyLine();
    void clearBlock();

    // Debug
    void printMatrices();

};

class interfaceTetris : public game
{
public:
    interfaceTetris();
    void newGame();
    void stopGame();
};
