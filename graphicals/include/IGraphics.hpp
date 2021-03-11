/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** GENERIC.hpp
*/

#ifndef __GENERIC_HPP_
#define __GENERIC_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include "Exception.hpp"

#define ASSETS "graphicals/sfml/assets/"
#define FONT "graphicals/sfml/font/"

#define CENTER_ORIGIN

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

enum Value {
    RETURN_SUCCESS = 0,
    RETURN_ERROR = 84,
    INPUT_NOTHING = -1,
    INPUT_CLOSE = 0,
    INPUT_N = 110, // Change le nameScore
    INPUT_A = 97,
    INPUT_E = 101,
    INPUT_O = 111,
    INPUT_P = 112,
    INPUT_R = 114,
    INPUT_M = 109,
    INPUT_ESCAPE = 27,
    INPUT_Z = 122,
    INPUT_S = 115,
    INPUT_Q = 113,
    INPUT_D = 100,
    INPUT_LEFT_RIGHT = 13,
    INPUT_UP = 14,
    INPUT_DOWN = 15,
    INPUT_VALIDE = 10,// '\n'
};

namespace arcade
{
    class IGraphics {
        public:
            IGraphics() = default;
            virtual ~IGraphics() = default;

            virtual char getEvent(void) = 0;
            virtual void print(display_t &display) = 0;
            virtual void destructor() = 0;
            virtual void refresh() = 0;

            virtual int getWindowHeight() = 0;
            virtual int getWindowWidth() = 0;
            virtual bool clockDisplay() = 0;
    };
}

typedef arcade::IGraphics *createLib_t(void);

#endif