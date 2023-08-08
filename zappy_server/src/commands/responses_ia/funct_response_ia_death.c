/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_death
*/

#include "zappy.h"

/**
 @brief connect death command response to gui
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param void *info: matches the ia structure
 @return void
**/
void funct_response_ia_death(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    (void)args;
    (void)com;
    SIZE = 6;
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    OCTETS[0] = '\0';
    strcat(OCTETS, "dead\n\0");
    write(ia->buffer.sock.sockfd, OCTETS, SIZE);
    printf("%sPlayer: %s%d%s is dead%s\n", P, R, ia->player->id, P, N);
}
