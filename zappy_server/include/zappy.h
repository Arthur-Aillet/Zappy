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

    #include "ia.h"
    #include "gui.h"
    #include "teams.h"
    #include "server.h"

typedef struct common_s {
    gui_t gui;
    ia_t *ia;
    size_t nb_teams;
    team_t *teams;
    server_t server;
    client_t *client;
    size_t port;
    size_t freq; //NOTE: - time unit
    time_t timer;
} common_t;


//-------------- Common Functions --------------------------------//

common_t set_common(int ac, char *av[]);
void free_common(common_t *com);

//---------------------------------------------------------------//

void check_error_output(common_t *com, int output, char *error);

void listening_sockets(common_t *com);

uint8_t **get_message(server_t *server, client_t *client);

#endif /* !ZAPPY_H_ */
