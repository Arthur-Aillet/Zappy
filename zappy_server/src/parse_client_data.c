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

//NOTE - size of the data buffer is 200 because you can receive a message
// with the command "Broadcast"
char **get_message(server_t *server, client_t *client)
{
    char data[200];
    char **arr = NULL;

    bzero(data, sizeof(data));
    if (read(client->socket, data, sizeof(data)) == 0) {
        printf("%sRead error: closed connection with %s%d%s\n",
        R, B, client->socket, N);
        client->socket = close_client(client->socket, server);
        return NULL;
    }
    if (data[strlen(data) - 1] == '\n')
        data[strlen(data) - 1] = '\0';
    arr = my_str_to_word_array(data, arr, ' ');
    return arr;
}
