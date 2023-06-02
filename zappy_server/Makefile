##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

SRC		=	src/listening_socket.c							\
			src/parser.c									\
			src/set_structure/set_client.c					\
			src/set_structure/set_team.c					\
			src/set_structure/set_common.c					\
			src/set_structure/set_gui.c						\
			src/set_structure/set_ia.c						\
			src/set_structure/set_parser.c					\
			src/commands/check_arguments.c					\
			src/commands/commands_gui/funct_client_mct.c	\
			src/commands/commands_gui/funct_client_msz.c	\
			src/commands/commands_gui/funct_client_pin.c	\
			src/commands/commands_gui/funct_client_plv.c	\
			src/commands/commands_gui/funct_client_ppo.c	\
			src/commands/commands_gui/funct_client_sgt.c	\
			src/commands/commands_gui/funct_client_sst.c	\
			src/commands/commands_gui/funct_client_tna.c	\

MAIN	=	src/main.c \

CC = gcc
OBJ = $(SRC:.c=.o)
MAINOBJ = $(MAIN:.c=.o)

NAME = zappy_server
CPPFLAGS = -I include/
#LDLIBS =
CFLAGS += -Wall -Wextra -g3

all: $(NAME)

$(NAME): $(OBJ) $(MAINOBJ)
	$(CC) -o $(NAME) $(OBJ) $(MAINOBJ) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

re: fclean all

clean:
	rm -f $(OBJ)
	rm -f $(MAINOBJ)

fclean: clean
	rm -f $(NAME)

.PHONY: all re clean fclean
