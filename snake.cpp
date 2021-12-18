#include "snake.h"

void Snake::init(vector<pair<int, int>> startingPos)
{
    body.clear();
    body.push_back(startingPos[0]);
    body.push_back(startingPos[1]);
    body.push_back(startingPos[2]);
}

void Snake::paint(int color1, int color2)
{
    for (int i = 0; i < body.size(); i++)
    {
        pair<int, int> location = body[i];
        move(location.first, location.second);
        init_pair(2, color1, color2);
        attron(COLOR_PAIR(2));
        addch('-');
        attroff(COLOR_PAIR(2));
    }
}

pair<int, int> Snake::slither(int direction)
{
    tail = body[body.size() - 1];
    body.pop_back();
    pair<int, int> old_head = body[0];
    pair<int, int> new_head = old_head;

    switch (direction)
    {
    case UP:
        new_head.first--;
        break;
    case DOWN:
        new_head.first++;
        break;
    case LEFT:
        new_head.second--;
        break;
    case RIGHT:
        new_head.second++;
        break;
    default:
        break;
    }

    body.insert(body.begin(), new_head);
    return new_head;
}

void Snake::grow()
{
    body.push_back(tail);
}

// CRITIC AREA: Implement with semaphores
bool Snake::has_collision()
{
    pair<int, int> head = body[0];
    int x = head.first, y = head.second;

    if (x == 0 || y == 0 || x == LINES - 1 || y == COLS - 1)
    {
        return true;
    }

    for (int i = 1; i < body.size(); i++)
    {
        if (head == body[i])
        {
            return true;
        }
    }
    return false;
}