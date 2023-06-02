/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** listening_socket.c
*/

#include "zappy.h"
#include <errno.h>
#include <sys/select.h>

static int create_new_client(int acc, client_t *client, server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (client[i].socket == 0) {
            client[i].socket = acc;
            FD_SET(acc, &server->read_fd);
            server->maxsd = (acc > server->maxsd) ? acc : server->maxsd;
            return 1;
        }
    }
    fprintf(stderr, "%sError: array of client is full%s\n", RED, NEUTRE);
    return 0;
}

static int new_client(server_t *server, client_t *client)
{
    struct sockaddr_in a_cli;
    int acc = accept(server->socket, (struct sockaddr *)&a_cli, &server->size);
    if (acc < 0) {
        if (errno != EWOULDBLOCK && errno != EAGAIN) {
            fprintf(stderr, "%saccept() failed%s\n", RED, NEUTRE);
            return 0;
        }
        return 1;
    }
    if (create_new_client(acc, client, server) == 0)
        return 0;
    return 1;
}

static int check_incoming_data(common_t *com) //NOTE - Transforms this function for create threads
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (PC_SOCKET(i) > 0 && FD_ISSET(PC_SOCKET(i), &PS_READ)) {
            get_message(&com->server, &com->client[i]);
        }
    }
    return 1;
}

void listening_sockets(common_t *com)
{
    if (FD_ISSET(PS_SOCKET, &PS_READ))
        check_error_output(com, new_client(&com->server, com->client), NULL);
    else
        check_error_output(com, check_incoming_data(com), NULL);
}
