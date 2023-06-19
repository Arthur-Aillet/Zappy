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
    strcpy(msg, "%s");
    strcat(msg, message);
    strcat(msg, "%s\n");
    fprintf(stderr, msg, color, N);
    free(msg);
    return ret;
}
