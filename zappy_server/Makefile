##
## EPITECH PROJECT, 2023
## Zappy
## File description:
## Makefile
##

LIB		=	src/my_str_to_word_array.c										\

SRC		=	src/listening_socket.c											\
			src/parser.c													\
			src/parse_client_data.c											\
			src/error_handling.c											\
			src/update_map.c												\
			src/update_life.c												\
			src/update_msg_queue.c											\
			src/find_ia.c													\
			src/set_structure/set_common.c									\
			src/set_structure/set_gui.c										\
			src/set_structure/set_ia.c										\
			src/set_structure/set_client.c									\
			src/set_structure/set_parser.c									\
			src/set_structure/set_team.c									\
			src/set_structure/set_player.c 									\
			src/set_structure/set_new_player.c								\
			src/commands/client_undefined.c									\

COMMAND	=	src/commands/check_command.c									\
			src/commands/common_functions.c									\
			src/commands/find_ia_for_command.c								\
			src/commands/common_functions_bis.c								\
			src/commands/create_struct_command.c							\
			src/commands/commands_gui/funct_client_bct.c					\
			src/commands/commands_gui/funct_client_mct.c					\
			src/commands/commands_gui/funct_client_msz.c					\
			src/commands/commands_gui/funct_client_pin.c					\
			src/commands/commands_gui/funct_client_plv.c					\
			src/commands/commands_gui/funct_client_ppo.c					\
			src/commands/commands_gui/funct_client_sgt.c					\
			src/commands/commands_gui/funct_client_sst.c					\
			src/commands/commands_gui/funct_client_tna.c					\
			src/commands/responses_gui/funct_server_all_bct.c				\
			src/commands/responses_gui/funct_server_bct.c					\
			src/commands/responses_gui/funct_server_ebo.c					\
			src/commands/responses_gui/funct_server_edi.c					\
			src/commands/responses_gui/funct_server_enw.c					\
			src/commands/responses_gui/funct_server_msz.c					\
			src/commands/responses_gui/funct_server_pbc.c					\
			src/commands/responses_gui/funct_server_pdi.c					\
			src/commands/responses_gui/funct_server_pdr.c					\
			src/commands/responses_gui/funct_server_pex.c					\
			src/commands/responses_gui/funct_server_pfk.c					\
			src/commands/responses_gui/funct_server_pgt.c					\
			src/commands/responses_gui/funct_server_pic.c					\
			src/commands/responses_gui/funct_server_pic_next.c				\
			src/commands/responses_gui/funct_server_pie.c					\
			src/commands/responses_gui/funct_server_pin.c					\
			src/commands/responses_gui/funct_server_plv.c					\
			src/commands/responses_gui/funct_server_pnw.c					\
			src/commands/responses_gui/funct_server_ppo.c					\
			src/commands/responses_gui/funct_server_sbp.c					\
			src/commands/responses_gui/funct_server_seg.c					\
			src/commands/responses_gui/funct_server_sgt.c					\
			src/commands/responses_gui/funct_server_smg.c					\
			src/commands/responses_gui/funct_server_sst.c					\
			src/commands/responses_gui/funct_server_suc.c					\
			src/commands/responses_gui/funct_server_tna.c					\
			src/commands/commands_ia/funct_client_ia_broadcast.c			\
			src/commands/commands_ia/funct_client_ia_check_ressources.c		\
			src/commands/commands_ia/funct_client_ia_connect_bar.c			\
			src/commands/commands_ia/funct_client_ia_connect_nbr.c			\
			src/commands/commands_ia/funct_client_ia_eject.c				\
			src/commands/commands_ia/funct_client_ia_fork.c					\
			src/commands/commands_ia/funct_client_ia_forward.c				\
			src/commands/commands_ia/funct_client_ia_incantation.c			\
			src/commands/commands_ia/funct_client_ia_incantation_bis.c		\
			src/commands/commands_ia/funct_create_check_incantation.c		\
			src/commands/commands_ia/funct_client_incantation_bis.c			\
			src/commands/commands_ia/funct_client_ia_inventory.c			\
			src/commands/commands_ia/funct_client_ia_left.c					\
			src/commands/commands_ia/funct_client_ia_look.c					\
			src/commands/commands_ia/funct_client_ia_msg.c					\
			src/commands/commands_ia/funct_client_ia_right.c				\
			src/commands/commands_ia/funct_client_ia_set_obj.c				\
			src/commands/commands_ia/funct_client_ia_take_obj.c				\
			src/commands/responses_ia/funct_response_ia_broadcast.c			\
			src/commands/responses_ia/funct_response_ia_broadcast_bis.c		\
			src/commands/responses_ia/funct_remove_player.c					\
			src/commands/responses_ia/funct_remove_player_bis.c				\
			src/commands/responses_ia/funct_find_post.c						\
			src/commands/responses_ia/funct_remove_egg.c					\
			src/commands/responses_ia/funct_response_ia_connect_bar.c		\
			src/commands/responses_ia/funct_response_ia_connect_nbr.c		\
			src/commands/responses_ia/funct_response_ia_death.c				\
			src/commands/responses_ia/funct_response_ia_eject.c				\
			src/commands/responses_ia/funct_response_ia_fork.c				\
			src/commands/responses_ia/funct_response_ia_forward.c			\
			src/commands/responses_ia/funct_response_ia_incantation.c		\
			src/commands/responses_ia/funct_response_ia_incantation_bis.c	\
			src/commands/responses_ia/funct_response_ia_inventory.c			\
			src/commands/responses_ia/funct_response_ia_inventory_bis.c		\
			src/commands/responses_ia/funct_response_ia_left.c				\
			src/commands/responses_ia/funct_response_look_player_egg.c		\
			src/commands/responses_ia/funct_response_look_ressources_one.c	\
			src/commands/responses_ia/funct_response_look_ressources_two.c	\
			src/commands/responses_ia/funct_response_look_est.c				\
			src/commands/responses_ia/funct_response_look_sud.c				\
			src/commands/responses_ia/funct_response_look_west.c			\
			src/commands/responses_ia/funct_response_look_north.c			\
			src/commands/responses_ia/funct_response_ia_msg.c				\
			src/commands/responses_ia/funct_response_ia_look.c				\
			src/commands/responses_ia/funct_response_ia_right.c				\
			src/commands/responses_ia/funct_response_ia_set_obj.c			\
			src/commands/responses_ia/funct_set_object_inventory.c			\
			src/commands/responses_ia/funct_take_object_inventory.c			\
			src/commands/responses_ia/funct_response_ia_take_obj.c			\


SRC +=	$(LIB) $(COMMAND)

MAIN	=	src/main.c \

CC = gcc
OBJ = $(SRC:.c=.o)
MAINOBJ = $(MAIN:.c=.o)

NAME = zappy_server
CPPFLAGS = -I include/ -Wall -Wextra
LDLIBS = -lm
CFLAGS += -Wall -Wextra

debug:	fclean $(OBJ) $(MAINOBJ)
	$(CC) -o $(NAME) $(OBJ) $(MAINOBJ) $(CFLAGS) -g3 $(LDFLAGS) $(LDLIBS) -g

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
