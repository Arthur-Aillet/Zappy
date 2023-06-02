/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** zappy.h
*/

#ifndef ZAPPY_H_
    #define ZAPPY_H_

    #define MAX_CLIENTS  20
    #define S_SOCKET    com.server.socket
    #define S_READ      com.server.read_fd
    #define S_MAX       com.server.maxsd

    #define PS_SOCKET    com->server.socket
    #define PS_READ      com->server.read_fd
    #define PS_MAX       com->server.maxsd

    #define PC_SOCKET(i) com->client[i].socket
    #include "ia.h"
    #include "gui.h"
    #include "teams.h"

    #include <sys/select.h>
    #include <sys/time.h>
    #include <sys/types.h>
    #include <unistd.h>

typedef struct server_s {
    int socket;
    int maxsd;
    struct sockaddr_in addr;
    fd_set read_fd;
    socklen_t size;
} server_t;

typedef struct client_s {
    int socket;
    struct sockaddr_in addr;
} client_t;

    #define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

typedef struct common_s {
    gui_t *gui;
    ia_t *ia;
    size_t nb_teams;
    team_t *teams;
    server_t server;
    client_t *client;
    size_t port;
    size_t freq; //NOTE: - time unit
} common_t;


//-------------- Common Functions --------------------------------//

common_t set_common(int ac, char *av[]);
void free_common(common_t *com);

//---------------------------------------------------------------//

//-------------- Client Functions -------------------------------//

client_t *set_clients(client_t *client);
int close_client(int client_socket, server_t *server);
void free_clients(client_t *cli, server_t *server);

//---------------------------------------------------------------//

void check_error_output(common_t *com, int output, char *error);

void listening_sockets(common_t *com);

uint8_t **get_message(server_t *server, client_t *client);

#endif /* !ZAPPY_H_ */