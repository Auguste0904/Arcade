##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

all:	nibbler pacman centipede qix solar_fox

nibbler:
			make -sC nibbler

pacman:
			make -sC pacman

centipede:
			make -sC centipede

qix:
			make -sC qix

solar_fox:
			make -sC solar_fox

clean:
			make -sC nibbler clean
			make -sC pacman clean
			make -sC centipede clean
			make -sC qix clean
			make -sC solar_fox clean

fclean: clean
			@rm -f $(shell find . -name "*~")
			@rm -f $(shell find . -name "a.out")
			@rm -f $(shell find . -name "vgcore.*")
			@rm -f $(shell find . -name "\#*#")
			@rm -f $(shell find . -name "*.gc*")
			@rm -f $(shell find . -name ".safe")
			make -sC nibbler fclean
			make -sC pacman fclean
			make -sC centipede fclean
			make -sC qix fclean
			make -sC solar_fox fclean

re:	fclean all

.PHONY:	all clean fclean re nibbler pacman centipede qix solar_fox
