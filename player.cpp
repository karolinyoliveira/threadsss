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

void Player::move(int key)
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
    return;
}


bool Player::check_collision(Player other_player)
{
    pair<int, int> head = snake.get_head();
    if (try_eating_food(head))
        {
            snake.grow();
            score++;
        }

    if (snake.has_collision())
        {
            return false;
        }

    vector<pair<int, int>> enemy_body = other_player.get_snake().get_body();
    for(int i=0; i<enemy_body.size(); i++) 
    {
        if (head == enemy_body[i]) {
            return false;
        }
    }
    return true;
}
