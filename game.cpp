#include "game.h"

int game_state = BEFORE_START;

int level;

Player p1;
Player p2;
int p1_idx, p2_idx;
Snake snakes[SNAKES];
int total_time=0;

sem_t player_semaphore;
void start_game()
{
    sem_init(&player_semaphore, 0, 1);

    p1_idx = 0;
    p2_idx = 1;
    for(int i=0; i<SNAKES; i++)
    {
        vector<pair<int, int>> start_position;
        start_position.push_back(make_pair(rand() % LINES, rand() % COLS));
        start_position.push_back(make_pair(start_position[0].first - 1, start_position[0].second));
        start_position.push_back(make_pair(start_position[1].first - 1, start_position[1].second));
        Snake snake;
        snake.init(start_position);
        snakes[i] = snake;
    }
    p1.set_controls('w', 's', 'a', 'd');
    p1.set_snake(snakes[p1_idx]);
    p1.init();

    p2.set_controls('A', 'B', 'D', 'C');
    p2.set_snake(snakes[p2_idx]);
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

    addstr("|||       Score P1: ");
    printw("%d - Score P2: %d | Difficulty: %s | TIME: %06d       |||", p1.get_score(), p2.get_score(), s, total_time);
}

void swap_snakes()
{
    if (total_time%SWAP_TIME==0) 
    {
        snakes[p1_idx] = p1.get_snake();
        snakes[p2_idx] = p2.get_snake();
        do {
            p1_idx = rand() % SNAKES;
            p2_idx = rand() % SNAKES;
        } while(p1_idx == p2_idx);
        p1.set_snake(snakes[p1_idx]);
        p2.set_snake(snakes[p2_idx]);
    }

    return;
}

void p1_movement(int key)
{
    sem_wait(&player_semaphore);
    if (!p1.move(key, 1, COLOR_GREEN))
    {
        endgame();
    }
    sem_post(&player_semaphore);
    return;
}

void p2_movement(int key)
{
    int new_key = key;
    if (key == '\033')
    {            // reading arrows
        getch(); // skipping '[' character
        new_key = getch();
    }


    sem_wait(&player_semaphore);
    if (!p2.move(new_key, 2, COLOR_YELLOW))
    {
        endgame();
    }
    sem_post(&player_semaphore);
    return;
}

bool game_logic(UI ui, int k, int dt)
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
        total_time += dt/10000;
        swap_snakes();
        for(int i=0; i<6; i++)
        {
            if (i != p1_idx && i != p2_idx)
            {
                snakes[i].paint(4, COLOR_RED);
            }
        }

        // ------------------------------ PLAYER 1 --------------------------------------
        std::thread t1(p1_movement, key);

        // ------------------------------ PLAYER 2 --------------------------------------
        std::thread t2(p2_movement, key);


        std::thread t3(paint_food);

        t1.join();
        t2.join();
        t3.join();
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