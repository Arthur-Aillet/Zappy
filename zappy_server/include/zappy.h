/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** zappy.h
*/

#ifndef ZAPPY_H_
    #define ZAPPY_H_

    #define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

    #define S_SOCKET            com.server.socket
    #define S_READ              com.server.read_fd
    #define S_MAX               com.server.maxsd

    #define PS_SOCKET           com->server.socket
    #define PS_READ             com->server.read_fd
    #define PS_MAX              com->server.maxsd

    #define PC_SOCKET(i)        com->client[i].socket

    #define SOCKET(i)           client[i].socket

    #define TEAM(i)             com->teams[i]

    #define C_DENSITY           com->gui->map.density
    #define C_RESSOURCES(y, x)  com->gui->map.tiles[y][x].ressources

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "ia.h"
    #include "gui.h"
    #include "teams.h"
    #include "server.h"

typedef struct common_s {
    gui_t *gui;
    ia_t *ia;
    size_t nb_ia;
    size_t nb_teams;
    team_t *teams;
    server_t server;
    client_t *client;
    size_t port;
    size_t freq; //NOTE: - time unit
    clock_t timer;
} common_t;

typedef struct msg_queue_s {
    double time;
    time_t start;
    char **msg;
    void (*handler)(char **args, void *info, common_t *com);
    //NOTE - pointeur sur fonctione qu'on doit executer
    struct msg_queue_s *next_msg;
} msg_queue_t;

//-------------- Responses Gui -----------------------------------//

void funct_server_msz(char **args, void *info, common_t *common);
void funct_server_bct(char **args, void *info, common_t *common);
void funct_server_all_bct(char **args, void *info, common_t *common);
void funct_server_tna(char **args, void *info, common_t *common);
void funct_server_pnw(char **args, void *info, common_t *common);
void funct_server_ppo(char **args, void *info, common_t *common);
void funct_server_plv(char **args, void *info, common_t *common);
void funct_server_pin(char **args, void *info, common_t *common);
void funct_server_pex(char **args, void *info, common_t *common);
void funct_server_pbc(char **args, void *info, common_t *common);
void funct_server_pic(char **args, void *info, common_t *common);
void funct_server_pie(char **args, void *info, common_t *common);
void funct_server_pfk(char **args, void *info, common_t *common);
void funct_server_pdr(char **args, void *info, common_t *common);
void funct_server_pgt(char **args, void *info, common_t *common);
void funct_server_pdi(char **args, void *info, common_t *common);
void funct_server_enw(char **args, void *info, common_t *common);
void funct_server_ebo(char **args, void *info, common_t *common);
void funct_server_edi(char **args, void *info, common_t *common);
void funct_server_sgt(char **args, void *info, common_t *common);
void funct_server_sst(char **args, void *info, common_t *common);
void funct_server_seg(char **args, void *info, common_t *common);
void funct_server_smg(char **args, void *info, common_t *common);
void funct_server_suc(char **args, void *info, common_t *common);
void funct_server_sbp(char **args, void *info, common_t *common);


//-------------- Common Functions --------------------------------//

common_t set_common(int ac, char *av[]);
egg_t set_egg(int x, int y);
void free_common(common_t *com);
ia_t *to_find_ia(char *n, common_t *common);
ia_t *to_find_ia_int(int n, common_t *common);
void free_arg(int nbr, char **arg);
void free_msg_queue(msg_queue_t *msg_queue);

//---------------------------------------------------------------//

void check_error_output(common_t *com, int output, char *error);

void listening_sockets(common_t *com);

char **get_message(server_t *server, client_t *client, common_t *com);
int undefined_client_command(char **command, common_t *com, int idx);
int check_slot_and_create_player(common_t *com, int team_idx,int client_idx);

int choose_ia_command(char **cmd, common_t *com, int i);

void update_life(client_t *client, server_t *server,
                size_t freq, common_t *com);

void malloc_nbr_args(msg_queue_t *new_msg, size_t nbr_args);
team_t *to_find_team_by_uint8_t(char *n, common_t *common);
team_t *to_find_team_by_int(int n, common_t *common);

void remove_player(player_t *ennemy, player_t *ia, common_t *com);
int find_post(common_t *com, ia_t *ia);
egg_t *remove_egg(egg_t egg, egg_t *old_eggs, size_t nb_eggs, common_t *com);

void inventory_mendiane(ia_t *ia);
void inventory_sibur(ia_t *ia);
void inventory_deraumere(ia_t *ia);
void inventory_linemate(ia_t *ia);
void inventory_food(ia_t *ia);

void next_if_funct_set(ia_t *ia, common_t *com, char **args);
void response_set(ia_t *ia, int idx, common_t *com);

void next_if_funct_take(ia_t *ia, common_t *com, char **args);
void response_take(ia_t *ia, int idx, common_t *com);

client_gui_t create_struct_client_gui(char **command);
server_ia_t create_struct_client_ia(char **command);
ia_t *find_ia_for_command(common_t *com, client_t *client);

void to_check_command_exist_ia(server_ia_t *server_ia, ia_t *ia,
                                common_t *com);
void to_check_command_exist_gui(client_gui_t *client_gui,
                                gui_t *gui, common_t *com);

void check_msg_queue_ia(common_t *com);

int to_check_ressources_bis(ia_t *ia, common_t *com, int x, int y);
int to_check_ressources(ia_t *ia, common_t *com, int x, int y);
char *create_new_arg(int nbr, msg_queue_t *new_msg);
void status_level_one(ia_t *ia, common_t *com, msg_queue_t *new_msg);
void status_level_two_tree(ia_t *ia,
                                common_t *com, msg_queue_t *new_msg);
void to_complete_ia_in_incantation(int nbr_ia,
                                char **arg, tile_t *tile);
void status_level_other(ia_t *ia, common_t *com, msg_queue_t *new_msg);
void status_level_four_five(ia_t *ia, common_t *com, msg_queue_t *new_msg);
void to_create_message_response_ia(msg_queue_t *new_msg);
void to_complete_ia_in_incantation_bis(int nbr_ia,
                                char **arg, tile_t *tile);
int to_find_ia_incantation(common_t *com, ia_t *ia);

void funct_server_pic_send_message(char **args, gui_t *gui);

char *prepare_arg_response_gui(int x);
int set_nbr_ia(ia_t *ia);
void remove_choose_player(player_t *ennemy, common_t *com, player_t *ia);
void funct_server_pic_level_other(char **args, gui_t *gui);
void funct_server_pic_level_four_five(char **args, gui_t *gui);

void funct_level_1(ia_t *ia, common_t *com);
void funct_prepare_response_gui_incantation(ia_t *ia, common_t *com, int r);

void to_take_ressources_response_ia(ia_t *ia, common_t *com,
                                                int x, int y);
void to_take_ressources_response_ia_deraumere(ia_t *ia,
                                        common_t *com, int x, int y);
void to_take_ressources_response_ia_food(ia_t *ia,
                                    common_t *com, int x, int y);
void funct_response_look_north(ia_t *ia, common_t *com);
void funct_response_look_sud(ia_t *ia, common_t *com);
void funct_response_look_est(ia_t *ia, common_t *com);
void funct_response_look_west(ia_t *ia, common_t *com);

void update_map(common_t *com);

void update_tile_gui(common_t *com, ia_t *ia);
void send_message_to_player(common_t *com, ia_t *ia, int i, char **args);

#endif /* !ZAPPY_H_ */
