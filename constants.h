#ifndef DEF_SETTING

#define DEF_SETTING

const int SPEEDEASY = 140000;
const int SPEEDMEDIUM = 100000;
const int SPEEDHARD = 70000;
const int BEFORE_START=0,START=1,ENDED=2;
const int FOOD_COUNT=5;

typedef struct controls
{
    int up, down, left, right;
} Controls;

#endif