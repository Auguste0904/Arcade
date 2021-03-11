/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** centipede.hpp
*/

#ifndef __CENTIPEDE_HPP_
#define __CENTIPEDE_HPP_

#include <iostream>
#include <exception>
#include "IGames.hpp"

namespace arcade
{
    class Centipede : public IGames
    {
        public:
            Centipede();
            virtual ~Centipede() = default;

            std::vector<display_t> &getInitState(); // Instancier les textures et set leur positions de départ au lancement du jeu
            std::vector<display_t> &getState(); // Set les positions des textures en jeu (à utiliser !!!)
            void move(char input); // Fonction la plus longu à coder... Sert de move automatiquement les sprites en jeu
            void restart(); //reset score
            uint64_t getScore(); // getScore
            arcade::statusGame &getStatus(); // getStatus (if INGAME / WIN / LOSE)
            bool speedGame(); // Vitesse du jeu en global, c'est à dire la vitesse des sprites -> return true if le snake avance je crois
        protected:
            std::vector<display_t> &displayMenu();
            std::vector<display_t> &displayGame();
            void moveMenu(char input);
            void moveGame(char input);
            void clearScreen();

            arcade::statusGame status = arcade::statusGame::INGAME;
            std::vector<display_t> state = {{"", "", "", "", 0, 0, true}};
            std::chrono::_V2::system_clock::time_point past_clock;
            std::chrono::milliseconds clock_time;
            uint8_t select = 0;
            bool isGame = false;
            std::vector<display_t> clear = {};
    };
}

#endif