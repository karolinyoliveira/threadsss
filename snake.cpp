#include "snake.h"

void Snake::init(vector<pair<int, int>> startingPos)
{
    facing_direction = 2;
    body.clear();
    body.push_back(startingPos[0]);
    body.push_back(startingPos[1]);
    body.push_back(startingPos[2]);
}

void Snake::paint(int nplayer, int color)
{
    for (int i = 0; i < body.size(); i++)
    {
        pair<int, int> location = body[i];
        move(location.first, location.second);
        init_pair(nplayer, color, color);
        attron(COLOR_PAIR(nplayer));
        addch('-');
        attroff(COLOR_PAIR(nplayer));
    }
}

vector<pair<int, int>> Snake::get_body()
{
    return body;
}

pair<int, int> Snake::get_head()
{
    return body[0];
}

pair<int, int> Snake::slither(Controls crtl, int direction)
{
    facing_direction = direction;
    tail = body[body.size() - 1];
    body.pop_back();
    pair<int, int> old_head = body[0];
    pair<int, int> new_head = old_head;

    if (direction == crtl.up)
    {
        facing_direction = 0;
        new_head.first = new_head.first - 1 < 0 ? LINES - 1 : new_head.first - 1;
    }
    if (direction == crtl.down)
    {
        facing_direction = 1;
        new_head.first = new_head.first + 1 > LINES - 1 ? 0 : new_head.first + 1;
    }
    if (direction == crtl.left)
    {
        facing_direction = 2;
        new_head.second = new_head.second - 1 < 0 ? COLS - 1 : new_head.second - 1;
    }
    if (direction == crtl.right)
    {
        facing_direction = 3;
        new_head.second = new_head.second + 1 > COLS - 1 ? 0 : new_head.second + 1;
    }

    body.insert(body.begin(), new_head);
    return new_head;
}

void Snake::grow()
{
    body.push_back(tail);
}

bool Snake::has_collision()
{
    pair<int, int> head = body[0];
    int x = head.first, y = head.second;

    for (int i = 1; i < body.size(); i++)
    {
        if (head == body[i])
        {
            return true;
        }
    }
    return false;
}