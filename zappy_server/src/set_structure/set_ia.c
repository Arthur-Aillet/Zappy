/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** set_ia.c
*/

#include "ia.h"
#include <stdlib.h>
#include "error_handling.h"
#include "zappy.h"

/**
 * @brief Reset a structure ia_t
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param ia_t *ia: the pointeur to a ia_t structure
 * @return void
*/
void close_ia(ia_t *ia)
{
    ia->buffer.bufferRead.usedSize = 0;
    ia->buffer.bufferRead.octets = NULL;
    ia->buffer.bufferWrite.usedSize = 0;
    ia->buffer.bufferWrite.octets = NULL;
    ia->buffer.sock.sockfd = 0;
    ia->player = NULL;
    ia->error = NULL;
    ia->msg_queue = NULL;
}

/**
 * @brief Set theia_t structure and all these values
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param void
 * @return ia_t *
*/
ia_t *set_ia(void)
{
    ia_t *ia = malloc(sizeof(ia_t) * MAX_PLAYER);
    if (ia == NULL)
        error("ia allocation failed", 0);
    for (int i = 0; i < MAX_PLAYER; i++) {
        close_ia(&ia[i]);
    }
    if (ia == NULL)
        exit(error("Failed to allocate ia", 84));
    return ia;
}

/**
 * @brief Free ia structure
 * @author Laetitia Bousch/ Ludo De-Chavagnac
 * @param ia_t *ia: the array of ia structures containing all data for ia
 * @return void
*/
void free_ia(ia_t *ia)
{
    if (ia == NULL)
        return;
    for (int i = 0; i < MAX_PLAYER; i++) {
        if (ia[i].buffer.bufferRead.octets != NULL)
            free(ia->buffer.bufferRead.octets);
        if (ia[i].buffer.bufferWrite.octets != NULL)
            free(ia[i].buffer.bufferWrite.octets);
        free_msg_queue(ia[i].msg_queue);
    }
    free(ia);
    basic_log("IA free", B, 0);
}
