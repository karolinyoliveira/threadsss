#ifndef DEF_SNAKE

#define DEF_SNAKE 
#include<curses.h>
#include<vector>
#include "constants.h"
using namespace std;

class Snake
{
private:
    int x, y;
    vector<pair<int, int>> body;
    pair<int, int> tail;

public:
    void init(vector<pair<int, int>> startingPos);
    void paint(int nplayer, int color);
    void grow();
    bool has_collision();
    vector<pair<int, int>> get_body();
    pair<int, int> get_head();
    pair<int, int> slither(Controls crtl, int direction);
    int facing_direction;
};

#endif