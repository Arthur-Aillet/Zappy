/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** error_handling.c
*/

#include "error_handling.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int error(char *message, int ret)
{
    char *msg = malloc(sizeof(char) * (strlen(message) + 10));

    if (msg == NULL) {
        fprintf(stderr, "%sMemory allocation failed%s\n", R, N);
        return 0;
    }
    strcpy(msg, "%s");
    strcat(msg, message);
    strcat(msg, "%s\n");
    fprintf(stderr, msg, R, N);
    free(msg);
    return ret;
}

int basic_log(char *message, char *color, int ret)
{
    char *msg = malloc(sizeof(char) * (strlen(message) + strlen(color) + 10));

    if (msg == NULL)
        return error("Memory allocation failed", 0);
    strcpy(msg, "%s");
    strcat(msg, message);
    strcat(msg, "%s\n");
    fprintf(stderr, msg, color, N);
    free(msg);
    return ret;
}
