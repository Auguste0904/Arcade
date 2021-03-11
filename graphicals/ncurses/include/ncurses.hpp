/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** NCurses.hpp
*/

#ifndef __NCURSES_HPP_
#define __NCURSES_HPP_

#include "IGraphics.hpp"
#include <ncurses.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <signal.h>


namespace arcade
{
    class NCurses : public IGraphics
    {
        public:
            NCurses();
            ~NCurses() = default;

            char getEvent(void);
            void print(display_t &print);
            void destructor();
            void refresh();

            int getWindowHeight();
            int getWindowWidth();
            bool clockDisplay();
        protected:
            void clearView();
            void activate_color(display_t &print);
            void desactivate_color(display_t &print);

            bool refreshView = false;
            int x;
            int y;
    };
}

#endif