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


#include <allegro.h>
#include <string>
#include <iostream>
#include <cstdio>


#define GAME_LOOP_SPEED_NORMAL 200
#define GAME_LOOP_SPEED_TURBO 50
#define GAME_CANVAS_START_X 20
#define GAME_CANVAS_START_Y 20
#define GAME_CANVAS_BACKGROUND makecol(0,0,0)
#define GAME_STATE_NEWSHAPE_COMEOUT 0
#define GAME_STATE_NEWSHAPE_FALL 1
#define GAME_MAX_X 16
#define GAME_MAX_Y 26

#define TETRIS_INTERFACE_MENU 0
#define TETRIS_INTERFACE_GAME 1
#define TETRIS_INTERFACE_HIGHSCORE 2

#define SHAPE_1A 0
#define SHAPE_1B 1
#define SHAPE_2A 2
#define SHAPE_2B 3
#define SHAPE_3A 4
#define SHAPE_3B 5
#define SHAPE_4 6
#define SHAPE_5A 7
#define SHAPE_5B 8
#define SHAPE_5C 9
#define SHAPE_5D 10
#define SHAPE_6A 11
#define SHAPE_6B 12
#define SHAPE_6C 13
#define SHAPE_6D 14
#define SHAPE_7A 15
#define SHAPE_7B 16
#define SHAPE_7C 17
#define SHAPE_7D 18

#define BLOCK_STATE_FLY 0
#define BLOCK_STATE_STONED 1

#define COLOR_WHITE makecol(255,255,255)
#define COLOR_RED makecol(255,0,0)
#define COLOR_GREEN makecol(0,255,0)
#define COLOR_BLUE makecol(0,0,255)
#define COLOR_BLACK makecol(0,0,0)

#define BLOCK_COLOR_BLACK 0
#define BLOCK_COLOR_RED 1
#define BLOCK_COLOR_YELLOW 2
#define BLOCK_COLOR_GREEN 3
#define BLOCK_COLOR_BLUE 4

#define GAME_NEXTSHAPE_START_X 420
#define GAME_NEXTSHAPE_START_Y 160
#define GAME_NEXTSHAPE_WIDTH 160
#define GAME_NEXTSHAPE_HEIGHT 160



using namespace std;
class game;
class logic;
class control;
class canvas;
class interfacegame;


