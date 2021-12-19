#include "game.h"

int direction_p1;
int direction_p2;
int game_state = BEFORE_START;

int score;
int high_score = 0;
int level;

Snake player1;
Snake player2;

void start_game()
{
    vector<pair<int, int>> position_p1;
    position_p1.push_back(make_pair(rand() % LINES, rand() % COLS));
    position_p1.push_back(make_pair(position_p1[0].first-1, position_p1[0].second));
    position_p1.push_back(make_pair(position_p1[1].first-1, position_p1[1].second));
    player1.init(position_p1);

    vector<pair<int, int>> position_p2;
    position_p2.push_back(make_pair(20, 0));
    position_p2.push_back(make_pair(20, 1));
    position_p2.push_back(make_pair(20, 2));
    player2.init(position_p2);

    init_food();
    score = 0;
    direction_p1 = LEFT;
    direction_p2 = LEFT;
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


        // ------------------------------ PLAYER 1 --------------------------------------
        if ((key == UP || key == UPA || key == UPB) && direction_p1 != DOWN)
        {
            direction_p1 = UP;
        }
        else if ((key == DOWN || key == DOWNB || key == DOWNA) && direction_p1 != UP)
        {
            direction_p1 = DOWN;
        }
        else if ((key == LEFT || key == LEFTA || key == LEFTB) && direction_p1 != RIGHT)
        {
            direction_p1 = LEFT;
        }
        else if ((key == RIGHT || key == RIGHTA || key == RIGHTB) && direction_p1 != LEFT)
        {
            direction_p1 = RIGHT;
        }
        pair<int, int> head = player1.slither(direction_p1);
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
        if (key=='\033') { // reading arrows
            getch(); // skipping '[' character
            key = getch();
            if (key == 'A' && direction_p2 != DOWN)
            {
                direction_p2 = UP;
            }
            else if (key == 'B' && direction_p2 != UP)
            {
                direction_p2 = DOWN;
            }
            else if (key == 'D' && direction_p2 != RIGHT)
            {
                direction_p2 = LEFT;
            }
            else if (key == 'C' && direction_p2 != LEFT)
            {
                direction_p2 = RIGHT;
            }
        }
        pair<int, int> head2 = player2.slither(direction_p2);
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