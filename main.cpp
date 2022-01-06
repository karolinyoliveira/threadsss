#include <iostream>
#include <unistd.h>
#include <curses.h>
#include "constants.h"
#include <chrono>
#include "ui.h"
#include "game.h"

using namespace std;

int set_speed(int mode)
{
    int speed;
    switch (mode)
    {
    case 1:
        speed = SPEEDEASY;
        break;
    case 2:
        speed = SPEEDMEDIUM;
        break;
    case 3:
        speed = SPEEDHARD;
        break;
    default:
        break;
    }
    return speed;
}

void event_loop(UI ui, int q, int delay)
{
    int dt;
    while (true)
    {
        auto last_time = chrono::system_clock::now();
        erase();

        bool a = game_logic(ui, q, dt);
        if (!a)
            break;
        refresh();

        do
        {
            auto current_time = chrono::system_clock::now();
            dt = chrono::duration_cast<std::chrono::microseconds>(current_time - last_time).count();
        } while (dt < delay);
    }
}

int main()
{
    cout << "\n\t\t 🐍 WELCOME TO THREADSSS! 🐍 \n\n";
    cout << "Use WASD to control the green snake and arrows to control the blue one.\n\n";
    cout << "Choose game mode\n\n";
    cout << " 1.Easy \n 2.Medium \n 3.Hard \n";
    cout << "Your choice: ";

    int mode;
    cin >> mode;
    if (mode < 1 || mode > 3)
    {
        cout << "\n Invalid mode, try again!" << endl;
        return 1;
    }
    int speed = set_speed(mode);

    UI ui;
    ui.init();
    event_loop(ui, mode, speed);
    ui.finish();
    cout << "\n\t\t\t🐍 GAME OVER! 🐍  \n\n";
}