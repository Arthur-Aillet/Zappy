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

uint8_t *get_message(server_t *server, client_t *client)
{
    char data[200];
    bzero(data, sizeof(data));
    if (read(client->socket, data, sizeof(data)) == 0) {
        client->socket = close_client(client->socket, server);
        return;
    }
    data[strlen(data) - 1] = '\0';
    char **arr = NULL;
    arr = my_str_to_word_array(data, arr, ' ');
    free_array(arr);
}