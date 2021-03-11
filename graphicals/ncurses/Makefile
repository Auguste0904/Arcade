##
## EPITECH PROJECT, 2019
## OOP_arcade_2019
## File description:
## Makefile
##

CC		=	g++

CFLAGS	+=	-I../include -I./include -I../../core/include -Wall -Wextra -W -lncurses

NAME	=	lib_arcade_ncurses.so

SRC		=	src/ncurses.cpp

OBJ		=	$(SRC:.cpp=.o)

all:	$(NAME)

%.o:	%.cpp
			@$(CC) -fPIC -shared $(CFLAGS) -c -o $@ $<
			@echo -e "\033[0;32m[OK]    \033[1;32m" $< "\033[0m"

$(NAME):	#$(OBJ)
			@echo -e "\033[1;32m\tnCurses:\033[0m"
			@$(CC) -fPIC -shared $(CFLAGS) $(SRC) -o $(NAME)
			@echo -e "\033[1;36m[OK]     \033[1;36mObj's files successfully compiled!\033[0m"
			@cp $(NAME) ../../lib/$(NAME)
#			@ld -shared $(OBJ) -o $(NAME)
			@echo -e "\033[1;36m[OK]    \033[1;36m" $(NAME) "successfully created!\033[1;33m"

clean:
			@rm -f $(OBJ)
			@echo -e "\033[1;33m[OK]     \033[1;33mOBJs successfully cleaned!\033[0m"

fclean:	clean
			@rm -f $(shell find . -name "*~")
			@rm -f $(shell find . -name "a.out")
			@rm -f $(shell find . -name "vgcore.*")
			@rm -f $(shell find . -name "\#*#")
			@rm -f $(shell find . -name "*.gc*")
			@rm -f $(shell find . -name ".safe")
			@rm -f $(NAME) ../$(NAME)
			@echo -e "\033[1;33m[OK]     \033[1;33mOBJs and useless files successfully cleaned!\033[0m"

re:	fclean all

.PHONY:	all clean fclean re
