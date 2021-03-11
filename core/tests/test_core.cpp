/*
** EPITECH PROJECT, 2019
** OOP_arcade_2019
** File description:
** tests.cpp
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>

#include "Core.hpp"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(run, test_arguments1, .exit_code = 84)
{
    char **av = static_cast<char **>(malloc(sizeof(char *)));

    av[0] = strdup("arcade");
    av[1] = NULL;
    arcade::Core core(1, av);

    cr_assert_eq(core.run(), 84);
}

// Test(run, test_arguments2, .exit_code = 84)
// {
//     arcade::Core core(3, av);

//     cr_expect_eq(core.run(), 84);
// }