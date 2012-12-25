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

#define GAME_LOOP_SPEED_NORMAL 50
#define GAME_LOOP_SPEED_TURBO 25
#define GAME_CANVAS_START_X 20
#define GAME_CANVAS_START_Y 0
#define GAME_CANVAS_BACKGROUND makecol(170, 238, 255)
#define GAME_STATE_NEWSHAPE_COMEOUT 0
#define GAME_STATE_NEWSHAPE_FALL 1

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

#define BLOCK_STATE_FLY 0
#define BLOCK_STATE_STONED 1

#define COLOR_WHITE makecol(255,255,255)
#define COLOR_RED makecol(255,0,0)
#define COLOR_GREEN makecol(0,255,0)
#define COLOR_BLUE makecol(0,0,255)
#define COLOR_BLACK makecol(0,0,0)


using namespace std;
