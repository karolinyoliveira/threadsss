#include <iostream>
#include <unistd.h>
#include <curses.h>
#include "settings_constant.h"
#include <chrono>
#include "ui.h"
#include "game.h"

using namespace std;

const int SPEEDEASY = 140000;
const int SPEEDMEDIUM = 100000;
const int SPEEDHARD = 70000;

// TODO: remove warning messages when make run is called
int set_speed(int mode)
{
    switch (mode)
    {
    case 1:
        return SPEEDEASY;
    case 2:
        return SPEEDMEDIUM;
    case 3:
        return SPEEDHARD;
    default:
        break;
    }
}

void event_loop(UI ui, int q, int delay)
{
    int dt;
    while (true)
    {
        auto last_time = chrono::system_clock::now();
        erase();

        bool a = game_logic(ui, q);
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