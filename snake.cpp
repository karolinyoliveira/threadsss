#include "snake.h"

// TODO: Implement snake with class

int x, y;
vector<pair<int, int>> bodySnake1;
vector<pair<int, int>> bodySnake2;

void init_snake(int player)
{
    switch (player)
    {
    case 1:
    {
        bodySnake1.clear();
        bodySnake1.push_back({10, 10});
        bodySnake1.push_back({10, 11});
        bodySnake1.push_back({10, 12});
        break;
    }
    case 2:
    {
        bodySnake2.clear();
        bodySnake2.push_back({20, 10});
        bodySnake2.push_back({20, 11});
        bodySnake2.push_back({20, 12});
        break;
    }
    default:
        break;
    }
}

void paint_snake(int player)
{
    switch (player)
    {
    case 1:
    {
        for (int i = 0; i < bodySnake1.size(); i++)
        {
            pair<int, int> location = bodySnake1[i];
            move(location.first, location.second);
            init_pair(2, COLOR_BLUE, COLOR_GREEN);
            attron(COLOR_PAIR(2));
            addch('-');
            attroff(COLOR_PAIR(2));
        }
        break;
    }
    case 2:
    {
        for (int i = 0; i < bodySnake2.size(); i++)
        {
            pair<int, int> location = bodySnake2[i];
            move(location.first, location.second);
            init_pair(2, COLOR_MAGENTA, COLOR_BLUE);
            attron(COLOR_PAIR(2));
            addch('-');
            attroff(COLOR_PAIR(2));
        }
        break;
    }
    default:
        break;
    }
}

pair<int, int> tailSnake1;

pair<int, int> move_snake(int direction)
{
    tailSnake1 = bodySnake1[bodySnake1.size() - 1];
    bodySnake1.pop_back();
    pair<int, int> old_head = bodySnake1[0];
    pair<int, int> new_head = old_head;

    if (direction == UP)
    {
        new_head.first--;
    }
    else if (direction == DOWN)
    {
        new_head.first++;
    }
    else if (direction == LEFT)
    {
        new_head.second--;
    }
    else if (direction == RIGHT)
    {
        new_head.second++;
    }
    bodySnake1.insert(bodySnake1.begin(), new_head);
    return new_head;
}

void grow_snake1()
{
    bodySnake1.push_back(tailSnake1);
}

void grow_snake2()
{
    bodySnake2.push_back(tailSnake2);
}

// CRITIC AREA: Implement with semaphores
bool has_collision()
{
    pair<int, int> head = bodySnake1[0];
    int x = head.first, y = head.second;

    if (x == 0 || y == 0 || x == LINES - 1 || y == COLS - 1)
    {
        return true;
    }

    for (int i = 1; i < bodySnake1.size(); i++)
    {
        if (head == bodySnake1[i])
        {
            return true;
        }
    }
    return false;
}