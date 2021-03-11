/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** SDL.hpp
*/

#ifndef __SDL_HPP_
#define __SDL_HPP_

#include "IGraphics.hpp"
#include "Exception.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <map>
#include <algorithm>

namespace arcade
{
    class Sdl : public IGraphics
    {
        public:
            Sdl();
            ~Sdl() = default;

            char getEvent(void);
            void print(display_t &print);
            void destructor();
            void refresh();

            int getWindowHeight();
            int getWindowWidth();
            bool clockDisplay();
        protected:
            char keyEvent();
            SDL_Texture *create_texture(const std::string &filename);
            void drawTexture(SDL_Texture *texture, display_t display);
            void create_text(display_t display);

            std::map<std::string, SDL_Texture *> sprite = {};
            SDL_Window *window;
            SDL_Event event = {0};
            SDL_Renderer *renderer;
            TTF_Font *font = NULL;
            int x = 0;
            int y = 0;
            std::chrono::_V2::system_clock::time_point past_clock;
            float clock_time;
    };
}

#endif