##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

all:	sfml sdl2 ncurses

sfml:
			make -sC sfml

sdl2:
			make -sC sdl2

ncurses:
			make -sC ncurses

clean:
			make -sC sfml clean
			make -sC sdl2 clean
			make -sC ncurses clean

fclean: clean
			@rm -f $(shell find . -name "*~")
			@rm -f $(shell find . -name "a.out")
			@rm -f $(shell find . -name "vgcore.*")
			@rm -f $(shell find . -name "\#*#")
			@rm -f $(shell find . -name "*.gc*")
			@rm -f $(shell find . -name ".safe")
			make -sC sfml fclean
			make -sC ncurses fclean
			make -sC sdl2 fclean

re:	fclean all

.PHONY:	all clean fclean re sfml sdl2 ncurses
