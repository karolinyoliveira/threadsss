#ifndef DEF_GAME

#define DEF_GAME
#include <thread>
#include <semaphore.h>
#include <curses.h>
#include <string.h>
#include "constants.h"
#include "ui.h"
#include "player.h"
#include "snake.h"
#include "food.h"

bool game_logic(UI ui, int k, int dt);
void endgame();
void time_out();

#endif