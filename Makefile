##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

all:	core games graphicals

core:
			@echo -e "\033[1;33m"
			make -sC core
			@echo -e "\033[1;0m"

games:
			@echo -e "\033[1;33m"
			make -sC games
			@echo -e "\033[1;0m"

graphicals:
			@echo -e "\033[1;33m"
			make -sC graphicals
			@echo -e "\033[1;0m"

tests_run:
			@echo -e "\033[1;33m"
			make -sC core tests_run
			@echo -e "\033[1;0m"

clean:
			@echo -e "\033[1;31m"
			make -sC core clean
			@echo -e "\033[1;31m"
			make -sC games clean
			@echo -e "\033[1;31m"
			make -sC graphicals clean

fclean: clean
			@rm -f $(shell find . -name "*~")
			@rm -f $(shell find . -name "a.out")
			@rm -f $(shell find . -name "vgcore.*")
			@rm -f $(shell find . -name "\#*#")
			@rm -f $(shell find . -name "*.gc*")
			@rm -f $(shell find . -name ".safe")
			@echo -e "\033[1;31m"
			make -sC core fclean
			@echo -e "\033[1;31m"
			make -sC games fclean
			@echo -e "\033[1;31m"
			make -sC graphicals fclean
			@rm -f ./arcade
			@rm -f ./lib/lib*

re:	fclean all

.PHONY:	all clean fclean re core games graphicals
