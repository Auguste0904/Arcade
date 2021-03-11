/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** nibbler.hpp
*/

#ifndef __NIBBLER_HPP_
#define __NIBBLER_HPP_

#include <iostream>
#include <exception>
#include <fstream>
#include <math.h>
#include "IGames.hpp"

namespace arcade
{
    enum DIR
    {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    typedef struct nibbler_node_s
    {
        arcade::DIR direction;
        int x;
        int y;
    } nibbler_node_t;

    typedef struct apple_node_s
    {
        int x;
        int y;
    } apple_node_t;

    class Nibbler : public IGames
    {
        public:
            Nibbler();
            virtual ~Nibbler() = default;

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
            void displayMap(std::vector<display_t> &tmp);
            void displaySnake(std::vector<display_t> &tmp);
            void moveMenu(char input);
            void moveGame(char input);
            void clearScreen();
            void createMap();
            void createComputeMap();
            void moveSnake();
            void createApple();
            void update_score();

            std::vector<apple_node_t> apple_node = {};
            std::vector<nibbler_node_t> nibbler_node = {};
            std::vector<std::string> map;
            std::vector<std::vector<int>> compute_map;
            arcade::statusGame status = arcade::statusGame::INGAME;
            std::vector<display_t> state = {{"", "", "", "", 0, 0, true}};
            std::chrono::_V2::system_clock::time_point past_clock;
            std::chrono::_V2::system_clock::time_point start_clock;
            std::chrono::_V2::system_clock::time_point current_clock;
            arcade::DIR direction = arcade::DIR::UP;
            std::chrono::duration<double, std::milli> delta;
            bool started = false;
            float clock_time;
            float time_finish;
            uint8_t select = 0;
            bool isGame = false;
            bool grow = false;
            std::vector<display_t> clear = {};
            int score = 0;
    };
}

#endif