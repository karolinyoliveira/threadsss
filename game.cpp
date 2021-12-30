#include "game.h"

int game_state = BEFORE_START;

int level;

Player p1;
Player p2;

void start_game()
{
    p1.set_controls('w', 's', 'a', 'd');
    p1.init();

    p2.set_controls('A', 'B', 'D', 'C');
    p2.init();

    init_food();

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

    switch (k)
    {
    case 1:
        strcpy(s, s1);
        break;
    case 2:
        strcpy(s, s2);
        break;
    case 3:
        strcpy(s, s3);
        break;
    default:
        break;
    }

    addstr("|||                  Score P1: ");
    printw("%d - Score P2: %d  Difficulty %s           |||", p1.get_score(), p2.get_score(), s);
}

bool game_logic(UI ui, int k)
{
    int key = getch();
    ui.paint();
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
        if (!p1.move(key, 1, COLOR_GREEN))
        {
            endgame();
        }

        // ------------------------------ PLAYER 2 --------------------------------------
        if (key == '\033')
        {            // reading arrows
            getch(); // skipping '[' character
            key = getch();
        }

        if (!p2.move(key, 2, COLOR_YELLOW))
        {
            endgame();
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