/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** pacman.hpp
*/

#ifndef __PACMAN_HPP_
#define __PACMAN_HPP_

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

    typedef struct apple_node_s
    {
        int x;
        int y;
    } apple_node_t;

    typedef struct ghost_node_s
    {
        float x;
        float y;
        std::string color;
        float time_spawn;
        arcade::DIR orientation;
    } ghost_node_t;

    class Pacman : public IGames
    {
        public:
            Pacman();
            virtual ~Pacman() = default;

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
            void displayGhosts(std::vector<display_t> &tmp);
            void moveMenu(char input);
            void moveGame(char input);
            void clearScreen();
            void createMap();
            void createComputeMap();
            void movePacman();
            void update_score();
            bool canSwitchDirection();
            void incrementScore();
            void moveGhost();

            std::vector<std::string> map;
            std::vector<std::vector<int>> compute_map;
            arcade::statusGame status = arcade::statusGame::INGAME;
            std::vector<display_t> state = {{"", "", "", "", 0, 0, true}};
            std::chrono::_V2::system_clock::time_point past_clock;
            std::chrono::_V2::system_clock::time_point start_clock;
            std::chrono::_V2::system_clock::time_point current_clock;
            std::chrono::_V2::system_clock::time_point animation_clock;
            std::chrono::_V2::system_clock::time_point ghost_clock;
            arcade::DIR direction = arcade::DIR::UP;
            arcade::DIR coming_direction = arcade::DIR::UP;
            std::chrono::duration<double, std::milli> delta;

            short animation_status;
            bool started = false;
            float clock_time;
            float time_finish;
            float time_animate;
            uint8_t select = 0;
            bool isGame = false;
            std::vector<display_t> clear = {};
            std::vector<ghost_node_t> ghost = {};
            int score = 0;
            float spawn_x = 0;
            float spawn_y = 0;
            float x = 0;
            float y = 0;
            bool ghosted = false;
    };
}

#endif