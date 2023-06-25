/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_response_ia_left
*/

#include "zappy.h"

/**
 @brief prepare response for the orientation
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param ia_t *ia: the ia structure
 @return void
**/
static void left_log(ia_t *ia)
{
    char dir[10];

    switch (ia->player->orientation) {
        case 1: sprintf(dir, "%s", "North");
            break;
        case 2: sprintf(dir, "%s", "East");
            break;
        case 3: sprintf(dir, "%s", "South");
            break;
        case 4: sprintf(dir, "%s", "Weast");
            break;
        default: sprintf(dir, "%s", "Undef");
            break;
    }
    printf("%sPlayer: %s%d%s turn to the left in %s%s%s\n", P, R,
            ia->player->id, P, B, dir, N);
}

/**
 @brief left command response to ia
 @author Laetitia Bousch/ Ludo De-Chavagnac
 @param common_t *common: common structure of all server data
 @param char **args: the arguments you need to answer the gui
 @param void *info: matches the ia structure
 @return void
**/
void funct_response_ia_left(char **args, void *info, common_t *com)
{
    ia_t *ia = (ia_t *)info;

    (void)args;
    (void)com;
    ia->player->orientation = (ia->player->orientation == North) ?
                                West : ia->player->orientation - 1;
    SIZE = 4;
    OCTETS = realloc(OCTETS, sizeof(char) * (SIZE));
    if (OCTETS == NULL) {
        return;
    }
    OCTETS[0] = '\0';
    strcat(OCTETS, "ok\n\0");
    write(ia->buffer.sock.sockfd, OCTETS, SIZE);
    left_log(ia);
}
