#include "ui.h"

void UI::init()
{
    initscr();

    nodelay(stdscr, TRUE);
    noecho();
    curs_set(0);
}

void UI::finish()
{
    endwin();
}

void UI::paint()
{
    start_color();
    attron(A_NORMAL);
    for (int i = 0; i < COLS; i++)
    {
        move(0, i);
        addch(border_char);
        move(LINES - 1, i);
        addch(border_char);
    }

    for (int i = 1; i < LINES - 1; i++)
    {
        move(i, 0);
        addch(border_char);
        move(i, COLS - 1);
        addch(border_char);
    }
    attroff(A_NORMAL);
}
