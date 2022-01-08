#ifndef DEF_PLAYER

#define DEF_PLAYER
#include <curses.h>
#include <vector>
#include <random>
#include <mutex>
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
    void set_snake(Snake s);
    Snake get_snake();
    int get_score();
    void set_controls(int up, int down, int left, int right);
    void init();
    void move(int key);
    bool check_collision(Player other_player);
};

#endif