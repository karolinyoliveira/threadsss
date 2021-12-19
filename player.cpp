#include "player.h"

void Player::set_controls(int up, int down, int left, int right)
{
    crtl.up = up;
    crtl.down = down;
    crtl.left = left;
    crtl.right = right;
}

int Player::get_score()
{
    return score;
}

void Player::init()
{
    direction = crtl.left;
    score = 0;

    vector<pair<int, int>> start_position;
    start_position.push_back(make_pair(rand() % LINES, rand() % COLS));
    start_position.push_back(make_pair(start_position[0].first - 1, start_position[0].second));
    start_position.push_back(make_pair(start_position[1].first - 1, start_position[1].second));
    snake.init(start_position);
}

bool Player::move(int key, int nplayer, int color)
{
    if (key == crtl.up && direction != crtl.down)
    {
        direction = crtl.up;
    }
    else if (key == crtl.down && direction != crtl.up)
    {
        direction = crtl.down;
    }
    else if (key == crtl.left && direction != crtl.right)
    {
        direction = crtl.left;
    }
    else if (key == crtl.right && direction != crtl.left)
    {
        direction = crtl.right;
    }

    pair<int, int> head = snake.slither(crtl, direction);
    snake.paint(nplayer, color);

    if (try_eating_food(head))
    {
        snake.grow();
        score++;
    }

    if (snake.has_collision())
    {
        return false;
    }
    return true;
}