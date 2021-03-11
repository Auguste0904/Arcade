/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** Error_handling.cpp
*/

#include "Core.hpp"

void arcade::Core::error_handling()
{
    void *tmp_ld = NULL;
    if (this->ac != 2)
        throw (arcade::Exception("Error: wrong number of arguments\nPlease try \"./arcade [lib]\""));
    tmp_ld = dlopen(this->av[1], RTLD_NOW);
    if (tmp_ld == NULL)
        throw (arcade::Exception(std::string(dlerror())));
    this->lib_list.push_back({this->av[1], tmp_ld, arcade::libType::GRAPHICAL});
}