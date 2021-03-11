/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** core.hpp
*/

#ifndef __CORE_HPP_
#define __CORE_HPP_

//#define DISPLAY_PERCENT

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <dlfcn.h>
#include <dirent.h>
#include <sys/stat.h>
#include <vector>
#include <unistd.h>

#include "IGraphics.hpp"
#include "IGames.hpp"
#include "Exception.hpp"

namespace arcade
{
    enum keys
    {
        CLOSE = 0,
        ESCAPE = 27
    };

    enum libType
    {
        GRAPHICAL,
        GAME
    };

    typedef struct lib_s
    {
        std::string name;
        void *handle;
        arcade::libType type;
    } lib_t;

    class Core
    {
        public:
            Core(int ac, char **av);
            ~Core() = default;

            int run();
        protected:
            void switch_lib();
            void switch_lib(void *handle);
            void error_handling();
            void launch_core();
            void launch_menu();
            void getLibrary();
            void getGames();
            bool hasEnding(std::string const &fullString, std::string const &ending);
            std::string get_string_end(std::string tmp);
            void launchGame(void *handle);
            void manage_menu_event();
            void print_menu();
            void clear();
            void getScore();
            void setScore();

            char event = 0;
            int ac;
            char **av;
            int which_lib = -1;
            arcade::IGraphics *graphics = NULL;
            arcade::IGames *game = NULL;
            std::string nickname = std::string("");
            std::vector<arcade::lib_t> lib_list = {};
            std::vector<arcade::lib_t> game_list = {};
            std::vector<arcade::lib_t> select_list = {};
            std::string best_score = "";
            uint64_t score = 0;
            int select_index = 0;
    };
};

#endif