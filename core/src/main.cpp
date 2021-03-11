/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** main.cpp
*/

#include "Core.hpp"
#include "Exception.hpp"

int main(const int ac, const char **av)
{
    arcade::Core core((int)ac, (char **)av);

    return (core.run());
}