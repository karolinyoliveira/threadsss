#ifndef DEF_SETTING

#define DEF_SETTING

const int SPEED_EASY = 140000;
const int SPEED_MEDIUM = 100000;
const int SPEED_HARD = 70000;
const int BEFORE_START=0,START=1,ENDED=2, TIMEOUT=3;
const int FOOD_COUNT=5;
const int SWAP_TIME=623;
const int SNAKES=3;
const int GAME_TIME_MILLI=60000;

typedef struct controls
{
    int up, down, left, right;
} Controls;

#endif