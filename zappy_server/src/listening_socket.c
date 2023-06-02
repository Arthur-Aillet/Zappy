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
        if (SOCKET(i) == 0) {
            SOCKET(i) = acc;
            FD_SET(acc, &server->read_fd);
            server->maxsd = (acc > server->maxsd) ? acc : server->maxsd;
            printf("%sCreate client: %s%d%s\n", GREEN, RED, SOCKET(i), NEUTRE);
            return 1;
        }
    }
    return error("Error: array of client is full", 0);
}

static int new_client(server_t *server, client_t *client)
{
    struct sockaddr_in a_cli;
    int acc = accept(server->socket, (struct sockaddr *)&a_cli, &server->size);
    if (acc < 0) {
        if (errno != EWOULDBLOCK && errno != EAGAIN)
            return error("accept() failed", 0);
        return 1;
    }
    if (create_new_client(acc, client, server) == 0)
        return 0;
    return 1;
}

//NOTE - Transforms this function for create threads
static int check_incoming_data(common_t *com)
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
