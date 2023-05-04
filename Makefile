##
## EPITECH PROJECT, 2021
## undefined
## File description:
## Makefile
##
SRC		=		Main.cpp			\
				Villager.cpp		\
				Druid.cpp

CXXFLAGS	=	-Iinclude -std=c++20

NAME	=		panoramix

$(eval SRC = $(addprefix src/, $(SRC)))

OBJ		=		$(SRC:.cpp=.o)

all:	$(NAME)


$(NAME):	$(OBJ)
		g++ -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:		fclean all