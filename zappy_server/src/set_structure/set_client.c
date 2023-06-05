/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_client.c
*/

#include "zappy.h"
#include <stdlib.h>

static client_t set_client(void)
{
    client_t cli;
    cli.socket = 0;
    cli.type = -1;
    cli.struct_client = NULL;
    return cli;
}

client_t *set_all_clients(void)
{
    client_t *client = malloc(sizeof(client_t) * (MAX_CLIENTS + 1));
    if (client == NULL)
        exit(error("Malloc error: Set clients", 84));
    for (int i = 0; i < MAX_CLIENTS; i++) {
        client[i] = set_client();
    }
    return client;
}

int close_client(int client_socket, server_t *server)
{
    if (client_socket != 0) {
        FD_CLR(client_socket, &server->read_fd);
        shutdown(client_socket, SHUT_RDWR);
        close(client_socket);
    }
    return 0;
}

void free_clients(client_t *cli, server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (cli[i].socket != 0) {
            cli[i].socket = close_client(cli[i].socket, server);
        }
    }
    free(cli);
}