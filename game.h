#ifndef DEF_GAME

#define DEF_GAME
#include <curses.h>
#include <string.h>
#include "constants.h"
#include "ui.h"
#include "player.h"
#include "snake.h"
#include "food.h"

bool game_logic(UI ui, int k);
void endgame();

#endif