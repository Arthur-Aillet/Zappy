/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** listening_socket.c
*/

#include <errno.h>
#include <string.h>
#include <sys/select.h>
#include <stdlib.h>

#include "zappy.h"

static int create_new_client(int acc, client_t *client, server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (SOCKET(i) <= 0) {
            SOCKET(i) = acc;
            client[i].type = UNDEFINED;
            FD_SET(acc, &server->read_fd);
            server->maxsd = (acc > server->maxsd) ? acc : server->maxsd;
            write(SOCKET(i), "WELCOME\n", 8);
            printf("%sCreate client: %s%d%s\n", G, R, SOCKET(i), N);
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

static int check_command(char **command, common_t *com, int cli_idx)
{
    server_ia_t ia;
    client_gui_t gui;

    if (command == NULL || command[0] == NULL || command[0][0] == '\0')
        return 1;
    if (com->client[cli_idx].type == IA) {
        ia = create_struct_client_ia(command);
        to_check_command_exist_ia(&ia,
                find_ia_for_command(com, &com->client[cli_idx]), com);
    } else if (com->client[cli_idx].type == GUI) {
        gui = create_struct_client_gui(command);
        to_check_command_exist_gui(&gui, com->gui, com);
    } else {
        undefined_client_command(command, com, cli_idx);
    }
    return 1;
}

static int check_incoming_data(common_t *com)
{
    char **command;

    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (PC_SOCKET(i) > 0 && FD_ISSET(PC_SOCKET(i), &PS_READ)) {
            command = get_message(&com->server, &com->client[i], com);
            int response = check_command(command, com, i);
            free_array((void**)command);
            return response;
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
