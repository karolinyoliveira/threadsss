#include "game.h"

int direction;
int game_state = BEFORE_START;

int score;
int high_score = 0;
int level;

Snake player1;
Snake player2;

void start_game()
{
    vector<pair<int, int>> position_p1;
    position_p1.push_back(make_pair(10, 10));
    position_p1.push_back(make_pair(10, 11));
    position_p1.push_back(make_pair(10, 12));
    player1.init(position_p1);
    
    vector<pair<int, int>> position_p2;
    position_p2.push_back(make_pair(20, 0));
    position_p2.push_back(make_pair(20, 1));
    position_p2.push_back(make_pair(20, 2));
    player2.init(position_p2);

    init_food();
    score = 0;
    direction = LEFT;
    game_state = START;
}

void endgame()
{
    game_state = ENDED;
}

void paint_score(int k)
{
    move(0, 6);
    char s[10];
    char s1[10] = "Easy", s2[10] = "Medium", s3[10] = "Hard";

    if (k == 1)
        strcpy(s, s1);
    else if (k == 2)
        strcpy(s, s2);
    else if (k == 3)
        strcpy(s, s3);
    addstr("|||                  Score ");
    printw("%d High Score %d  Difficulty %s           |||", score, high_score, s);
}

// TODO: Create a class to save infos like snake, controls and score for a specific player
bool game_logic(int k)
{
    int key = getch();
    paint_border();
    paint_score(k);
    if (game_state == BEFORE_START)
    {
        move(10, 15);
        addstr("press spacebar to start playing best playing when full screen");
        if (key == 32)
        {
            start_game();
        }
    }
    else if (game_state == START)
    {
        if ((key == UP || key == UPA || key == UPB) && direction != DOWN)
        {
            direction = UP;
        }
        else if ((key == DOWN || key == DOWNB || key == DOWNA) && direction != UP)
        {
            direction = DOWN;
        }
        else if ((key == LEFT || key == LEFTA || key == LEFTB) && direction != RIGHT)
        {
            direction = LEFT;
        }
        else if ((key == RIGHT || key == RIGHTA || key == RIGHTB) && direction != LEFT)
        {
            direction = RIGHT;
        }
        pair<int, int> head = player1.slither(direction);

        player1.paint(COLOR_GREEN,COLOR_GREEN);

        if (try_eating_food(head))
        {
            player1.grow();
            score++;
        }

        if (player1.has_collision())
        {
            endgame();
            if (score > high_score)
                high_score = score;
        }




        // ------------------------------ PLAYER 2 --------------------------------------
        /*
        if (key == 38 && direction != DOWN)
        {
            direction = UP;
        }
        else if (key == 40 && direction != UP)
        {
            direction = DOWN;
        }
        else if (key == 37 && direction != RIGHT)
        {
            direction = LEFT;
        }
        else if (key == 39 && direction != LEFT)
        {
            direction = RIGHT;
        }
        pair<int, int> head2 = player2.slither(direction);

        player2.paint(COLOR_YELLOW,COLOR_YELLOW);

         if (try_eating_food(head2))
        {
            player2.grow();
            score++;
        }

        if (player2.has_collision())
        {
            endgame();
            if (score > high_score)
                high_score = score;
        }
        */

        paint_food();
    }
    else
    {
        move(10, 45);
        addstr("GAME OVER!!!\n \t\t\t\t\t\t press spacebar to restart \n \t\t\t\t\t\t press q to quit");

        if (key == 32)
        {
            game_state = START;
            start_game();
        }
        else if (key == 113)
        {
            return false;
        }
    }

    return true;
}