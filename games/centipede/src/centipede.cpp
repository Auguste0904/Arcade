/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** nibbler.cpp
*/

#include "centipede.hpp"

arcade::Centipede::Centipede()
{
    this->past_clock = std::chrono::system_clock::now();
    this->clock_time = std::chrono::milliseconds(100);
}

std::vector<display_t> &arcade::Centipede::getInitState()
{
    return (this->getState());
}

arcade::statusGame &arcade::Centipede::getStatus()
{
    return (this->status);
}

std::vector<display_t> &arcade::Centipede::displayGame()
{
    this->state = {};
    return (this->state);
}

std::vector<display_t> &arcade::Centipede::displayMenu()
{
    static display_t play = {"Not available yet... Work in progress !", "", "", "", -10, 0, true};
    std::vector<display_t> tmp = {play};

    this->state = tmp;
    return (this->state);
}

void arcade::Centipede::clearScreen()
{
    display_t display_clear = {" ", "", "", "", 0, 0, true};

    for (float i = -100; i < 100; i++) {
        for (float j = -100; j < 100; j++) {
            display_clear = {" ", "", "", "", j, i, true};
            this->clear.push_back(display_clear);
        }
    }
}

std::vector<display_t> &arcade::Centipede::getState()
{
    if (this->clear.size() > 0) {
        this->state = this->clear;
        this->clear = {};
        return (this->state);
    }
    if (this->isGame)
        return (this->displayGame());
    else
        return (this->displayMenu());
}

bool arcade::Centipede::speedGame()
{
    if (std::chrono::system_clock::now() + this->clock_time >= this->past_clock) {
        this->past_clock = std::chrono::system_clock::now();
        return (true);
    } else
        return (false);
}

uint64_t arcade::Centipede::getScore()
{
    return (0);
}

void arcade::Centipede::restart()
{
    this->status = arcade::statusGame::INGAME;
}

void arcade::Centipede::moveMenu(char input)
{
    if (input == 10 && this->select == 1)
        this->status = arcade::statusGame::WIN;
    if (input == 10 && this->select == 0) {
        this->clearScreen();
        this->isGame = true;
    }
}

void arcade::Centipede::moveGame(char input)
{
    if (input == 27)
        this->isGame = false;
}

void arcade::Centipede::move(char input)
{
    static char buffer_input = -1;

    if (buffer_input == input)
        input = -1;
    if (input == 27 && !this->isGame)
        this->status = arcade::statusGame::WIN;
    buffer_input = input;
}

extern "C" arcade::IGames *create()
{
    return (new arcade::Centipede());
}