#include "game.h"

int game_state = BEFORE_START;

int level, winner;

Player p1;
Player p2;
vector<pair<int, int>> MAP;
int p1_idx, p2_idx;
Snake snakes[SNAKES];
int total_time = 0;

sem_t player_semaphore;
void start_game()
{
    sem_init(&player_semaphore, 0, 1);

    p1_idx = 0;
    p2_idx = 1;
    for (int i = 0; i < SNAKES; i++)
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

void update_map()
{
    MAP.clear();
    vector<pair<int, int>> body_p1 = p1.get_snake().get_body();
    vector<pair<int, int>> body_p2 = p2.get_snake().get_body();
    MAP.insert(MAP.end(), body_p1.begin()+1, body_p1.end());
    MAP.insert(MAP.end(), body_p2.begin()+1, body_p2.end());
}

bool player_collided(Player player) // checking if snakes are overlapping
{
    pair<int, int> head = player.get_snake().get_head();
    if(std::find(MAP.begin(), MAP.end(), head) != MAP.end())
    {
        return true;
    }

    return false;
}

void endgame()
{
    game_state = ENDED;
}

void time_out()
{
    game_state = TIMEOUT;
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

    int available_time = GAME_TIME_MILLI - total_time;
    if (available_time < 0)
    {
        available_time = 0;
    }

    addstr("|||       Score P1: ");
    printw("%d - Score P2: %d | Difficulty: %s | TIME: %06d       |||", p1.get_score(), p2.get_score(), s, available_time);
}

void swap_snakes()
{
    if (total_time % SWAP_TIME == 0)
    {
        snakes[p1_idx] = p1.get_snake();
        snakes[p2_idx] = p2.get_snake();
        do
        {
            p1_idx = rand() % SNAKES;
            p2_idx = rand() % SNAKES;
        } while (p1_idx == p2_idx);
        p1.set_snake(snakes[p1_idx]);
        p2.set_snake(snakes[p2_idx]);
    }
    return;
}

void p1_movement(int key)
{
    p1.move(key);
    p1.check_collision();

    sem_wait(&player_semaphore);
    p1.get_snake().paint(1, COLOR_GREEN);
    if (player_collided(p1))
    {
        winner = 2;
        endgame();
    }
    update_map();
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
    p2.move(new_key);
    p2.check_collision();

    sem_wait(&player_semaphore);
    p2.get_snake().paint(2, COLOR_YELLOW);
    if (player_collided(p2))
    {
        winner = 1;
        endgame();
    }
    update_map();
    sem_post(&player_semaphore);
    return;
}

bool game_logic(UI ui, int k, int dt)
{
    int key = getch();
    ui.paint();
    paint_score(k);

    switch (game_state)
    {
    case BEFORE_START:
    {
        move(10, 15);
        addstr("press spacebar to start playing :)");
        if (key == 32)
        {
            start_game();
        }
        break;
    }
    case START:
    {
        total_time += dt / 10000;
        if (total_time >= GAME_TIME_MILLI)
        {
            time_out();
            break;
        }

        swap_snakes();
        for (int i = 0; i < 6; i++)
        {
            if (i != p1_idx && i != p2_idx)
            {
                snakes[i].paint(4, COLOR_RED);
            }
        }

        thread t1(p1_movement, key);
        thread t2(p2_movement, key);

        thread t3(paint_food);

        t1.join();
        t2.join();
        t3.join();
        break;
    }
    case ENDED:
    {
        move(10, 45);
        printw("GAME OVER!!!\n \t\t\t\t\t\t Player %d wins!!!\n \t\t\t\t\t\t Press spacebar to restart \n \t\t\t\t\t\t Or press q to quit", winner);

        break;
    }
    case TIMEOUT:
    {
        move(10, 45);
        if (p1.get_score() == p2.get_score())
        {
            printw("GAME OVER!!!\n \t\t\t\t\t\t It's a tie!!!\n \t\t\t\t\t\t Press spacebar to restart \n \t\t\t\t\t\t Or press q to quit");
        }
        else if (p1.get_score() > p2.get_score())
        {
            winner = 1;
            printw("GAME OVER!!!\n \t\t\t\t\t\t Player %d wins!!!\n \t\t\t\t\t\t Press spacebar to restart \n \t\t\t\t\t\t Or press q to quit", winner);
        }
        else
        {
            winner = 2;
            printw("GAME OVER!!!\n \t\t\t\t\t\t Player %d wins!!!\n \t\t\t\t\t\t Press spacebar to restart \n \t\t\t\t\t\t Or press q to quit", winner);
        }
        break;
    }
    }

    if (game_state == ENDED || game_state == TIMEOUT)
    {
        if (key == 32)
        {
            game_state = START;
            total_time = 0;
            start_game();
        }
        else if (key == 113)
        {
            return false;
        }
    }
    return true;
}