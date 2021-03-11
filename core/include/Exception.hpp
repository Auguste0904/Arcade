/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** core.hpp
*/

#ifndef __EXCEPTION_HPP_
#define __EXCEPTION_HPP_

#include <exception>
#include <string>

namespace arcade
{
    class Exception: public std::exception
    {
        public:
            Exception(const std::string &message) throw();
            Exception() throw();
            ~Exception() throw() = default;

            virtual const char *what() const throw();
        protected:
            std::string message = "An error occured";
    };
}

#endif