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

static int check_ctrl_d(void)
{
    int stdin_flags = fcntl(0, F_GETFL, 0);
    fcntl(0, F_SETFL, stdin_flags | O_NONBLOCK);
    char buf[10];
    int ret = read(0, buf, sizeof(buf));
    if (ret == 0 || (ret < 0 && errno != EAGAIN))
        return 1;
    return 0;
}

int main(int ac, char *av[])
{
    common_t com = set_common(ac, av);
    while (1) {
        if (check_ctrl_d() == 1)
            break;
        set_new_loop(&com.server, com.client);
        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 0;
        if (select(S_MAX + 1, &S_READ, NULL, NULL, &timeout) < 0
        && (errno != EINTR)) {
            free_common(&com);
            exit(error("Select failed", 84));
        }
        listening_sockets(&com);
        update_map(&com.gui.map);
    }
    free_common(&com);
    return 0;
}
