/*
** EPITECH PROJECT, 2023
** B-YEP-400-PAR-4-1-zappy-laetitia.bousch
** File description:
** funct_remove_egg
*/

#include "zappy.h"

static void funct_find_egg(egg_t *new_eggs, size_t nb_eggs,
                            egg_t *old_eggs, egg_t egg)
{
    size_t nb = 0;

    if (new_eggs == NULL) {
        return;
    }
    for (size_t tmp = 0; tmp < nb_eggs; tmp++) {
        if (egg.egg_id != old_eggs[tmp].egg_id) {
            new_eggs[tmp].egg_id = old_eggs[tmp].egg_id;
            new_eggs[tmp].x = old_eggs[tmp].x;
            new_eggs[tmp].y = old_eggs[tmp].y;
            nb++;
        }
    }
}

egg_t *remove_egg(egg_t egg, egg_t *old_eggs, size_t nb_eggs, common_t *com)
{
    egg_t *new_eggs = malloc(sizeof(egg_t) * (nb_eggs - 1));
    u_int8_t **args = malloc(sizeof(u_int8_t *) * 1);
    char buffer_egg[256];

    if (args == NULL || new_eggs == NULL) {
        return NULL;
    }
    sprintf(buffer_egg, "%d", egg.egg_id);
    args[0] = malloc(sizeof(u_int8_t) * strlen(buffer_egg));
    if (args[0] == NULL) {
        return NULL;
    }
    args[0][0] = '\0';
    strcat((char*)args[0], buffer_egg);
    funct_find_egg(new_eggs, nb_eggs, old_eggs, egg);
    funct_server_edi(args, com->gui, com);
    return new_eggs;
}
