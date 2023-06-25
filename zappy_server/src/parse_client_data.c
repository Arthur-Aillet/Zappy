/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** parse_client_data.c
*/

#include "zappy.h"
#include "errno.h"
#include <stdlib.h>
#include <string.h>

static void close_client_data(server_t *server, client_t *client,
                            common_t *com)
{
    if (client->type == GUI) {
        com->gui->buffer.sock.sockfd = 0;
    }
    if (client->type == IA) {
        ia_t *ia = find_ia_for_command(com, client);
        free_msg_queue(ia->msg_queue);
        close_ia(ia);
    }
    client->socket = close_client(client->socket, server);
    client->type = UNDEFINED;
    client->str_cli = NULL;
}

//NOTE - size of the data buffer is 200 because you can receive a message
// with the command "Broadcast"
char **get_message(server_t *server, client_t *client, common_t *com)
{
    char data[2048];
    char **arr = NULL;

    bzero(data, sizeof(data));
    if (read(client->socket, data, sizeof(data)) == 0) {
        printf("%sRead error: closed connection with %s%d%s\n",
        R, B, client->socket, N);
        close_client_data(server, client, com);
        return NULL;
    }
    if (data[strlen(data) - 1] == '\n')
        data[strlen(data) - 1] = '\0';
    arr = my_str_to_word_array(data, arr, ' ');
    return arr;
}
