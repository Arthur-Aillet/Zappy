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

char **convert_arr_to_unit8(char **arr)
{
    size_t size = 0;
    char **res;

    for (; arr[size] != NULL; size++);
    res = malloc(sizeof(char *) * (size + 1));
    for (size_t i = 0; i < size; i++) {
        res[i] = malloc(sizeof(char) * (strlen(arr[i]) + 1));
        strcpy(res[i], arr[i]);
    }
    res[size] = NULL;
    return res;
}

//NOTE - size of the data buffer is 200 because you can receive a message
// with the command "Broadcast"
char **get_message(server_t *server, client_t *client)
{
    char **res;
    char data[200];
    char **arr = NULL;

    bzero(data, sizeof(data));
    if (read(client->socket, data, sizeof(data)) == 0) {
        printf("%sRead error: closed connection with %s%d%s\n",
        R, B, client->socket, N);
        client->socket = close_client(client->socket, server);
        return NULL;
    }
    data[strlen(data) - 1] = '\0';
    arr = my_str_to_word_array(data, arr, ' ');
    res = convert_arr_to_unit8(arr);
    free_array((void**)arr);
    return res;
}
