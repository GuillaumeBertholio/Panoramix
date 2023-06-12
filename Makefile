##
## EPITECH PROJECT, 2021
## undefined
## File description:
## Makefile
##

SRC		=		main.c		\
				pano.c		\
				villager.c

$(eval SRC = $(addprefix src/, $(SRC)))

CFLAGS	=	-Iinclude

NAME	=		panoramix

OBJ		=		$(SRC:.c=.o)

all:	$(NAME)

$(NAME):	$(OBJ)
		gcc -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:		fclean all