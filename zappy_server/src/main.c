/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** main
*/

#include "zappy.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

void check_error_output(common_t *com, int output, char *error)
{
    if (output == 0) {
        free_common(com);
        if (error != NULL)
            fprintf(stderr, error);
        exit(84);
    }
}

static void set_new_loop(server_t *server, client_t *cli)
{
    FD_ZERO(&server->read_fd);
    FD_SET(server->socket, &server->read_fd);
    server->maxsd = server->socket;

    for (size_t i = 0; i < MAX_CLIENTS; i++) {
        if (cli[i].socket > 0) {
            FD_SET(cli[i].socket, &server->read_fd);
            int flags = fcntl(cli[i].socket, F_GETFL, 0);
            fcntl(cli[i].socket, F_SETFL, flags | O_NONBLOCK);
        }
        if (cli[i].socket > server->maxsd)
            server->maxsd = cli[i].socket;
    }
}

//TODO - create a function for checking the Ctrl-D (exit the program)
int main(int ac, char *av[])
{
    common_t com = set_common(ac, av);
    while (1) {
        set_new_loop(&com.server, com.client);
        if (select(S_MAX + 1, &S_READ, NULL, NULL, NULL) < 0
        && (errno != EINTR)) {
            free_common(&com);
            fprintf(stderr, "%sSelect failed%s\n", RED, NEUTRE);
            exit(84);
        }
        listening_sockets(&com);
    }
    return 0;
}
