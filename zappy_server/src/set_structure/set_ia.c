/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_ia.c
*/

#include "ia.h"
#include <stdlib.h>
#include "error_handling.h"

ia_t close_ia(void)
{
    ia_t ia;
    ia.buffer.bufferRead.usedSize = 0;
    ia.buffer.bufferRead.octets = NULL;
    ia.buffer.bufferWrite.usedSize = 0;
    ia.buffer.bufferWrite.octets = NULL;
    ia.buffer.sock.sockfd = 0;
    ia.player = NULL;
    ia.error = NULL;
    ia.msg_queue = NULL;

    return ia;
}

ia_t *set_ia(void)
{
    ia_t *ia = malloc(sizeof(ia_t) * MAX_PLAYER);
    if (ia == NULL)
        error("ia allocation failed", 0);
    for (int i = 0; i < MAX_PLAYER; i++) {
        ia[i] = close_ia();
    }
    if (ia == NULL)
        exit(error("Failed to allocate ia", 84));
    return ia;
}

void free_ia(ia_t *ia)
{
    free(ia);
    basic_log("IA free", B, 0);
}
