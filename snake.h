#ifndef DEF_SNAKE

#define DEF_SNAKE 
#include<curses.h>
#include<vector>
#include "settings_constant.h"
using namespace std;

void init_snake(int player);
void paint_snake(int player);
pair<int, int> move_snake(int direction);
void grow_snake1();
bool has_collision();
#endif