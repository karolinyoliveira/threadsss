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
    score = 0;
}

void Player::set_snake(Snake s)
{
    snake = s;
    switch(snake.facing_direction) {
        case 0:
            direction = crtl.up;
            break;
        case 1:
            direction = crtl.down;
            break;
        case 2:
            direction = crtl.left;
            break;
        case 3:
            direction = crtl.right;
            break;
    }
}

Snake Player::get_snake()
{
    return snake;
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
    snake.facing_direction = direction;

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