/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** main.cpp
*/

#include "Exception.hpp"

arcade::Exception::Exception(const std::string &message) throw()
{
    this->message = message;
}

arcade::Exception::Exception() throw()
{
    ;
}

const char *arcade::Exception::what() const throw()
{
    return (this->message.c_str());
}