/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** IGames.hpp
*/

#ifndef __IGAMES_HPP_
#define __IGAMES_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>

#ifndef DISPLAY_T
#define DISPLAY_T

typedef struct display_s {
 std::string ascii;
 std::string foreground;
 std::string background;
 std::string image;
 float x;
 float y;
 bool isPrint;
} display_t;

#endif

namespace arcade
{
    enum statusGame {
        INGAME,
        WIN,
        LOSE,
    };

    class IGames
    {
        public:
            virtual ~IGames() = default;

            virtual std::vector<display_t> &getInitState() = 0; // utilité ???
            virtual std::vector<display_t> &getState() = 0;
            virtual void move(char input) = 0; // move auto
            virtual void restart() = 0; //reset score
            virtual uint64_t getScore() = 0; // getScore
            virtual arcade::statusGame &getStatus() = 0; // getStatus
            virtual bool speedGame() = 0;
    };
}

typedef arcade::IGames *createGame_t(void);

#endif