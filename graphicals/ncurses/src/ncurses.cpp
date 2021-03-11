/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** ncurses.cpp
*/

#include "ncurses.hpp"

arcade::NCurses::NCurses()
{
    initscr();
    start_color();
    // init_pair(1, COLOR_RED, COLOR_BLACK);
    curs_set(0);
    timeout(0);
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
    getmaxyx(stdscr, this->y, this->x);
    clear();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);
}

void arcade::NCurses::destructor()
{
    endwin();
}

char arcade::NCurses::getEvent()
{
    int event = getch();
    std::vector<int> vector = {};

    if (event == 27) {
        vector.push_back(event);
        while ((event = getch()) != -1) {
            vector.push_back(event);
        }
        if (vector.size() == 1)
            return (27);
        else
            return (-1);
    }
    while (getch() != -1);
    if (event == 258)
        return (-32);
    if (event == 259)
        return (-33);
    if (event == 260)
        return (-34);
    if (event == 261)
        return (-35);
    if (event == 122)
        return (122);
    if (event == 113)
        return (113);
    if (event == 115)
        return (115);
    if (event == 100)
        return (100);
    if (event > 127)
        return (-1);
    return (event);
}

int arcade::NCurses::getWindowHeight()
{
    int x = 0;
    int y = 0;

    getmaxyx(stdscr, y, x);
    return (y);
}

int arcade::NCurses::getWindowWidth()
{
    int x = 0;
    int y = 0;

    getmaxyx(stdscr, y, x);
    (void)y;
    return (x);
}

bool arcade::NCurses::clockDisplay()
{
    return (true);
}

void arcade::NCurses::clearView()
{
    display_t tmp = {" ", "", "", "", 0 , 0, true};

    for (int i = 0 - this->y / 2; i <= 0 + this->y / 2; i++) {
        for (int j = 0 - this->x / 2; j <= 0 + this->x / 2; j++) {
            tmp.x = j;
            tmp.y = i;
            this->print(tmp);
        }
    }
}

void arcade::NCurses::refresh(void)
{
    wrefresh(stdscr);
    this->refreshView = true;
}

void arcade::NCurses::activate_color(display_t &print)
{
    if (!print.foreground.compare("blue"))
        attron(COLOR_PAIR(1));
    else if (!print.foreground.compare("cyan"))
        attron(COLOR_PAIR(2));
    else if (!print.foreground.compare("green"))
        attron(COLOR_PAIR(3));
    else if (!print.foreground.compare("magenta"))
        attron(COLOR_PAIR(4));
    else if (!print.foreground.compare("red"))
        attron(COLOR_PAIR(5));
    else if (!print.foreground.compare("white"))
        attron(COLOR_PAIR(6));
    else if (!print.foreground.compare("yellow"))
        attron(COLOR_PAIR(7));
}

void arcade::NCurses::desactivate_color(display_t &print)
{
    if (!print.foreground.compare("blue"))
        attroff(COLOR_PAIR(1));
    else if (!print.foreground.compare("cyan"))
        attroff(COLOR_PAIR(2));
    else if (!print.foreground.compare("green"))
        attroff(COLOR_PAIR(3));
    else if (!print.foreground.compare("magenta"))
        attroff(COLOR_PAIR(4));
    else if (!print.foreground.compare("red"))
        attroff(COLOR_PAIR(5));
    else if (!print.foreground.compare("white"))
        attroff(COLOR_PAIR(6));
    else if (!print.foreground.compare("yellow"))
        attroff(COLOR_PAIR(7));
}

void arcade::NCurses::print(display_t &display)
{
    if (this->refreshView == true) {
        this->refreshView = false;
        this->clearView();
    }
    if (!display.isPrint || !display.ascii[0])
        return;
    this->activate_color(display);
    #ifndef CENTER_ORIGIN
    mvprintw(display.y, display.x, display.ascii.c_str());
    #else
    mvprintw(display.y + this->y / 2, display.x + this->x / 2, display.ascii.c_str());
    #endif
    this->desactivate_color(display);
    // if (!display.foreground.compare("RED"))
    //     attroff(COLOR_PAIR(1));
}

extern "C" arcade::IGraphics *create()
{
    return (new arcade::NCurses());
}