/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_client.c
*/

#include "zappy.h"
#include <stdlib.h>

client_t * set_clients(client_t *client)
{
    client = malloc(sizeof(client_t) * MAX_CLIENTS);
    if (client == NULL) {
        fprintf(stderr, "%sMalloc error: Set clients%s\n", RED, NEUTRE);
        exit(84);
    }
    client_t cli;
    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        cli.socket = 0;
        client[i] = cli;
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
            close_client(cli[i].socket, server);
        }
    }
    free(cli);
}