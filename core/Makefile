##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##


CC		=	g++

CFLAGS	+=	-I./include -I./../graphicals/include -I./../games/include -Wall -Wextra -W -ldl -g3

NAME	=	arcade

TNAME		=	unit_tests

SRC		=	src/Exception.cpp		\
			src/Core.cpp			\
			src/Error_handling.cpp	\
			src/LaunchGame.cpp

MAIN	=	src/main.cpp

TSRC	=	tests/test_core.cpp

OBJ		=	$(SRC:.cpp=.o)

CRIT	=	-lcriterion --coverage

all:	$(NAME)

%.o:	%.cpp
			@$(CC) -fPIC $(CFLAGS) -c -o $@ $<
			@echo -e "\033[0;32m[OK]    \033[1;32m" $< "\033[0m"

$(NAME):	$(OBJ)
			@echo -e "\033[1;36m[OK]     \033[1;36mObj's files successfully compiled!\033[0m"
			@$(CC) -o $(NAME) $(MAIN) $(OBJ) $(CFLAGS)
			@mv $(NAME) ../
			@echo -e "\033[1;36m[OK]    \033[1;36m" $(NAME) "successfully created!\033[0m"

clean:
			@rm -f $(OBJ)
			@echo -e "\033[1;33m[OK]     \033[1;33mOBJs successfully cleaned!\033[0m"

tests_run:	re
			@$(CC) $(TSRC) -o $(TNAME) $(SRC) $(CFLAGS) $(CRIT)
			./$(TNAME)
			gcovr

fclean:	clean
			@rm -f $(shell find . -name "*~")
			@rm -f $(shell find . -name "a.out")
			@rm -f $(shell find . -name "vgcore.*")
			@rm -f $(shell find . -name "\#*#")
			@rm -f $(shell find . -name "*.gc*")
			@rm -f $(shell find . -name ".safe")
			@rm -f ../$(NAME)
			@rm -f $(TNAME)
			@echo -e "\033[1;33m[OK]     \033[1;33mOBJs and useless files successfully cleaned!\033[0m"

re:	fclean all

.PHONY:	all clean fclean re
