##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

LIB		=	src/my_str_to_word_array.c		\

SRC		=	src/listening_socket.c									\
			src/parser.c											\
			src/parse_client_data.c									\
			src/error_handling.c									\
			src/set_structure/set_common.c							\
			src/set_structure/set_gui.c								\
			src/set_structure/set_ia.c								\
			src/set_structure/set_client.c							\
			src/set_structure/set_parser.c							\
			src/set_structure/set_team.c							\
			src/commands/check_command.c							\
			src/commands/commands_gui/funct_client_mct.c			\
			src/commands/commands_gui/funct_client_msz.c			\
			src/commands/commands_gui/funct_client_pin.c			\
			src/commands/commands_gui/funct_client_plv.c			\
			src/commands/commands_gui/funct_client_ppo.c			\
			src/commands/commands_gui/funct_client_sgt.c			\
			src/commands/commands_gui/funct_client_sst.c			\
			src/commands/commands_gui/funct_client_tna.c			\
			src/commands/commands_ia/funct_client_ia_connect_bar.c	\
			src/commands/commands_ia/funct_client_ia_death.c		\
			src/commands/commands_ia/funct_client_ia_eject.c		\
			src/commands/commands_ia/funct_client_ia_fork.c			\
			src/commands/commands_ia/funct_client_ia_incantation.c	\
			src/commands/commands_ia/funct_client_ia_mct.c			\
			src/commands/commands_ia/funct_client_ia_msz.c			\
			src/commands/commands_ia/funct_client_ia_pin.c			\
			src/commands/commands_ia/funct_client_ia_plv.c			\
			src/commands/commands_ia/funct_client_ia_ppo.c			\
			src/commands/commands_ia/funct_client_ia_set_obj.c		\
			src/commands/commands_ia/funct_client_ia_sgt.c			\
			src/commands/commands_ia/funct_client_ia_sst.c			\
			src/commands/commands_ia/funct_client_ia_take_obj.c		\
			src/commands/commands_ia/funct_client_ia_tna.c			\

SRC +=	$(LIB)

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
