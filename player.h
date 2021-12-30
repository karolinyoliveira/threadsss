#ifndef DEF_PLAYER

#define DEF_PLAYER
#include <curses.h>
#include <vector>
#include <random>
#include "constants.h"
#include "snake.h"
#include "food.h"

using namespace std;

class Player
{
private:
    Controls crtl;
    int direction;
    Snake snake;
    int score;
public:
    int get_score();
    void set_controls(int up, int down, int left, int right);
    void init();
    bool move(int key, int nplayer, int color);
};

#endif