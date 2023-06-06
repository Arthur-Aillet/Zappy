/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** zappy.h
*/

#ifndef ZAPPY_H_
    #define ZAPPY_H_

    #define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
    #define MAX_CLIENTS     MAX_PLAYER

    #define S_SOCKET        com.server.socket
    #define S_READ          com.server.read_fd
    #define S_MAX           com.server.maxsd

    #define PS_SOCKET       com->server.socket
    #define PS_READ         com->server.read_fd
    #define PS_MAX          com->server.maxsd

    #define PC_SOCKET(i)    com->client[i].socket

    #define SOCKET(i)       client[i].socket

    #define TEAM(i)         com->teams[i]

    #include <stdio.h>
    #include <stdlib.h>

    #include "ia.h"
    #include "gui.h"
    #include "teams.h"
    #include "server.h"

typedef struct common_s {
    gui_t gui;
    ia_t *ia;
    size_t nb_ia;
    size_t nb_teams;
    team_t *teams;
    server_t server;
    client_t *client;
    size_t port;
    size_t freq; //NOTE: - time unit
    time_t timer;
} common_t;


//-------------- Responses Gui -----------------------------------//

void funct_server_msz(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_bct(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_all_bct(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_tna(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_pnw(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_ppo(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_plv(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_pin(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_pex(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_pbc(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_pic(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_pie(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_pfk(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_pdr(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_pgt(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_pdi(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_enw(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_ebo(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_edi(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_sgt(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_sst(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_seg(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_smg(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_suc(uint8_t **args, gui_t *gui, common_t *common);
void funct_server_sbp(uint8_t **args, gui_t *gui, common_t *common);

//-------------- Common Functions --------------------------------//

common_t set_common(int ac, char *av[]);
void free_common(common_t *com);

//---------------------------------------------------------------//

void check_error_output(common_t *com, int output, char *error);

void listening_sockets(common_t *com);

uint8_t **get_message(server_t *server, client_t *client);
int undefined_client_command(uint8_t **command, common_t *com, int idx);

#endif /* !ZAPPY_H_ */
