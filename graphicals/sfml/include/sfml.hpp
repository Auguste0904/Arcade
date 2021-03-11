/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** sfml.hpp
*/

#ifndef __SFML_HPP_
#define __SFML_HPP_

#include "IGraphics.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

namespace arcade
{
    class Sfml : public IGraphics
    {
        public:
            Sfml();
            ~Sfml() = default;

            char getEvent(void);
            void print(display_t &print);
            void destructor();
            void refresh();

            int getWindowHeight();
            int getWindowWidth();
            bool clockDisplay();
        protected:
            sf::Sprite *create_sprite(const std::string &filename);
            void draw_text(display_t &display);

            std::map<std::string, sf::Sprite *> sprite;
            sf::RenderWindow *window;
            sf::Font font;
            std::unique_ptr<sf::View> view;
            sf::Shader *shade = NULL;
            std::chrono::_V2::system_clock::time_point past_clock;
            float clock_time;
    };
}

#endif