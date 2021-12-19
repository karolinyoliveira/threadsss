#ifndef DEF_UI

#define DEF_UI

#include <curses.h>

class UI
{
private:
    char border_char = '#';
public:
    void init();
    void finish();
    void paint();
};

#endif